//--------------------------------------------------------------
// File     : usbh_hid_core.c
//--------------------------------------------------------------

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "usbh_hid_core.h"
#include "usbh_hid_mouse.h"
#include "usbh_hid_keybd.h"





__ALIGN_BEGIN HID_Machine_TypeDef        HID_Machine __ALIGN_END ;
__ALIGN_BEGIN HID_Report_TypeDef         HID_Report __ALIGN_END ;
__ALIGN_BEGIN USB_Setup_TypeDef          HID_Setup __ALIGN_END ;
__ALIGN_BEGIN USBH_HIDDesc_TypeDef       HID_Desc __ALIGN_END ; 

__IO uint8_t start_toggle = 0;


static USBH_Status USBH_HID_InterfaceInit  (USB_OTG_CORE_HANDLE *pdev , 
                                            void *phost);

static void  USBH_ParseHIDDesc (USBH_HIDDesc_TypeDef *desc, uint8_t *buf);

static void USBH_HID_InterfaceDeInit  (USB_OTG_CORE_HANDLE *pdev , 
                                       void *phost);

static USBH_Status USBH_HID_Handle(USB_OTG_CORE_HANDLE *pdev , 
                                   void *phost);

static USBH_Status USBH_HID_ClassRequest(USB_OTG_CORE_HANDLE *pdev , 
                                         void *phost);

static USBH_Status USBH_Get_HID_ReportDescriptor (USB_OTG_CORE_HANDLE *pdev, 
                                                  USBH_HOST *phost,
                                                  uint16_t length);

static USBH_Status USBH_Get_HID_Descriptor (USB_OTG_CORE_HANDLE *pdev,\
                                            USBH_HOST *phost,  
                                            uint16_t length);

static USBH_Status USBH_Set_Idle (USB_OTG_CORE_HANDLE *pdev, 
                                  USBH_HOST *phost,
                                  uint8_t duration,
                                  uint8_t reportId);

static USBH_Status USBH_Set_Protocol (USB_OTG_CORE_HANDLE *pdev, 
                                      USBH_HOST *phost,
                                      uint8_t protocol);


USBH_Class_cb_TypeDef  HID_cb = 
{
  USBH_HID_InterfaceInit,
  USBH_HID_InterfaceDeInit,
  USBH_HID_ClassRequest,
  USBH_HID_Handle
};


//--------------------------------------------------------------
static USBH_Status USBH_HID_InterfaceInit ( USB_OTG_CORE_HANDLE *pdev, 
                                           void *phost)
{	
  uint8_t maxEP;
  USBH_HOST *pphost = phost;
    
  uint8_t num =0;
  USBH_Status status = USBH_BUSY ;
  HID_Machine.state = HID_ERROR;
  
  
  if(pphost->device_prop.Itf_Desc[0].bInterfaceSubClass  == HID_BOOT_CODE)
  {
    /*Decode Bootclass Protocl: Mouse or Keyboard*/
    if(pphost->device_prop.Itf_Desc[0].bInterfaceProtocol == HID_KEYBRD_BOOT_CODE)
    {
      HID_Machine.cb = &HID_KEYBRD_cb;
    }
    else if(pphost->device_prop.Itf_Desc[0].bInterfaceProtocol  == HID_MOUSE_BOOT_CODE)		  
    {
      HID_Machine.cb = &HID_MOUSE_cb;
    }
    
    HID_Machine.state     = HID_IDLE;
    HID_Machine.ctl_state = HID_REQ_IDLE; 
    HID_Machine.ep_addr   = pphost->device_prop.Ep_Desc[0][0].bEndpointAddress;
    HID_Machine.length    = pphost->device_prop.Ep_Desc[0][0].wMaxPacketSize;
    HID_Machine.poll      = pphost->device_prop.Ep_Desc[0][0].bInterval ;
    
    if (HID_Machine.poll  < HID_MIN_POLL) 
    {
       HID_Machine.poll = HID_MIN_POLL;
    }

    
    /* Check fo available number of endpoints */
    /* Find the number of EPs in the Interface Descriptor */      
    /* Choose the lower number in order not to overrun the buffer allocated */
    maxEP = ( (pphost->device_prop.Itf_Desc[0].bNumEndpoints <= USBH_MAX_NUM_ENDPOINTS) ? 
             pphost->device_prop.Itf_Desc[0].bNumEndpoints :
                 USBH_MAX_NUM_ENDPOINTS); 
    
    
    /* Decode endpoint IN and OUT address from interface descriptor */
    for (num=0; num < maxEP; num++)
    {
      if(pphost->device_prop.Ep_Desc[0][num].bEndpointAddress & 0x80)
      {
        HID_Machine.HIDIntInEp = (pphost->device_prop.Ep_Desc[0][num].bEndpointAddress);
        HID_Machine.hc_num_in  =\
               USBH_Alloc_Channel(pdev, 
                                  pphost->device_prop.Ep_Desc[0][num].bEndpointAddress);
        
        /* Open channel for IN endpoint */
        USBH_Open_Channel  (pdev,
                            HID_Machine.hc_num_in,
                            pphost->device_prop.address,
                            pphost->device_prop.speed,
                            EP_TYPE_INTR,
                            HID_Machine.length); 
      }
      else
      {
        HID_Machine.HIDIntOutEp = (pphost->device_prop.Ep_Desc[0][num].bEndpointAddress);
        HID_Machine.hc_num_out  =\
                USBH_Alloc_Channel(pdev, 
                                   pphost->device_prop.Ep_Desc[0][num].bEndpointAddress);
        
        /* Open channel for OUT endpoint */
        USBH_Open_Channel  (pdev,
                            HID_Machine.hc_num_out,
                            pphost->device_prop.address,
                            pphost->device_prop.speed,
                            EP_TYPE_INTR,
                            HID_Machine.length); 
      }
      
    }   
    
     start_toggle =0;
     status = USBH_OK; 
  }
  else
  {
    pphost->usr_cb->DeviceNotSupported();   
  }
  
  return status;
  
}


//--------------------------------------------------------------
void USBH_HID_InterfaceDeInit ( USB_OTG_CORE_HANDLE *pdev,
                               void *phost)
{	
   //USBH_HOST *pphost = phost;
    
  if(HID_Machine.hc_num_in != 0x00)
  {   
    USB_OTG_HC_Halt(pdev, HID_Machine.hc_num_in);
    USBH_Free_Channel  (pdev, HID_Machine.hc_num_in);
    HID_Machine.hc_num_in = 0;     /* Reset the Channel as Free */  
  }
  
  if(HID_Machine.hc_num_out != 0x00)
  {   
    USB_OTG_HC_Halt(pdev, HID_Machine.hc_num_out);
    USBH_Free_Channel  (pdev, HID_Machine.hc_num_out);
    HID_Machine.hc_num_out = 0;     /* Reset the Channel as Free */  
  }
 
  start_toggle = 0;
}


//--------------------------------------------------------------
static USBH_Status USBH_HID_ClassRequest(USB_OTG_CORE_HANDLE *pdev , 
                                         void *phost)
{   
    USBH_HOST *pphost = phost;
    
  USBH_Status status         = USBH_BUSY;
  USBH_Status classReqStatus = USBH_BUSY;
  
  
  /* Switch HID state machine */
  switch (HID_Machine.ctl_state)
  {
  case HID_IDLE:  
  case HID_REQ_GET_HID_DESC:
    
    /* Get HID Desc */ 
    if (USBH_Get_HID_Descriptor (pdev, pphost, USB_HID_DESC_SIZE)== USBH_OK)
    {
      
      USBH_ParseHIDDesc(&HID_Desc, pdev->host.Rx_Buffer);
      HID_Machine.ctl_state = HID_REQ_GET_REPORT_DESC;
    }
    
    break;     
  case HID_REQ_GET_REPORT_DESC:
    
    
    /* Get Report Desc */ 
    if (USBH_Get_HID_ReportDescriptor(pdev , pphost, HID_Desc.wItemLength) == USBH_OK)
    {
      HID_Machine.ctl_state = HID_REQ_SET_IDLE;
    }
    
    break;
    
  case HID_REQ_SET_IDLE:
    
    classReqStatus = USBH_Set_Idle (pdev, pphost, 0, 0);
    
    /* set Idle */
    if (classReqStatus == USBH_OK)
    {
      HID_Machine.ctl_state = HID_REQ_SET_PROTOCOL;  
    }
    else if(classReqStatus == USBH_NOT_SUPPORTED) 
    {
      HID_Machine.ctl_state = HID_REQ_SET_PROTOCOL;        
    } 
    break; 
    
  case HID_REQ_SET_PROTOCOL:
    /* set protocol */
    if (USBH_Set_Protocol (pdev ,pphost, 0) == USBH_OK)
    {
      HID_Machine.ctl_state = HID_REQ_IDLE;
      
      /* all requests performed*/
      status = USBH_OK; 
    } 
    break;
    
  default:
    break;
  }
  
  return status; 
}


//--------------------------------------------------------------
static USBH_Status USBH_HID_Handle(USB_OTG_CORE_HANDLE *pdev , 
                                   void   *phost)
{
  USBH_HOST *pphost = phost;
  USBH_Status status = USBH_OK;
  
  switch (HID_Machine.state)
  {
    
  case HID_IDLE:
    HID_Machine.cb->Init();
    HID_Machine.state = HID_SYNC;
    
  case HID_SYNC:

    /* Sync with start of Even Frame */
    if(USB_OTG_IsEvenFrame(pdev) == TRUE)
    {
      HID_Machine.state = HID_GET_DATA;  
    }
    break;
    
  case HID_GET_DATA:

    USBH_InterruptReceiveData(pdev, 
                              HID_Machine.buff,
                              HID_Machine.length,
                              HID_Machine.hc_num_in);
    start_toggle = 1;
    
    HID_Machine.state = HID_POLL;
    HID_Machine.timer = HCD_GetCurrentFrame(pdev);
    break;
    
  case HID_POLL:
    if(( HCD_GetCurrentFrame(pdev) - HID_Machine.timer) >= HID_Machine.poll)
    {
      HID_Machine.state = HID_GET_DATA;
    }
    else if(HCD_GetURB_State(pdev , HID_Machine.hc_num_in) == URB_DONE)
    {
      if(start_toggle == 1) /* handle data once */
      {
        start_toggle = 0;
        HID_Machine.cb->Decode(HID_Machine.buff);
      }
    }
    else if(HCD_GetURB_State(pdev, HID_Machine.hc_num_in) == URB_STALL) /* IN Endpoint Stalled */
    {
      
      /* Issue Clear Feature on interrupt IN endpoint */ 
      if( (USBH_ClrFeature(pdev, 
                           pphost,
                           HID_Machine.ep_addr,
                           HID_Machine.hc_num_in)) == USBH_OK)
      {
        /* Change state to issue next IN token */
        HID_Machine.state = HID_GET_DATA;
        
      }
      
    }      
    break;
    
  default:
    break;
  }
  return status;
}


//--------------------------------------------------------------
static USBH_Status USBH_Get_HID_ReportDescriptor (USB_OTG_CORE_HANDLE *pdev,
                                                  USBH_HOST *phost,
                                                  uint16_t length)
{
  
  USBH_Status status;
  
  status = USBH_GetDescriptor(pdev,
                              phost,
                              USB_REQ_RECIPIENT_INTERFACE
                                | USB_REQ_TYPE_STANDARD,                                  
                                USB_DESC_HID_REPORT, 
                                pdev->host.Rx_Buffer,
                                length);
  
  /* HID report descriptor is available in pdev->host.Rx_Buffer.
  In case of USB Boot Mode devices for In report handling ,
  HID report descriptor parsing is not required.
  In case, for supporting Non-Boot Protocol devices and output reports,
  user may parse the report descriptor*/
  
  
  return status;
}


//--------------------------------------------------------------
static USBH_Status USBH_Get_HID_Descriptor (USB_OTG_CORE_HANDLE *pdev,
                                            USBH_HOST *phost,
                                            uint16_t length)
{
  
  USBH_Status status;
  
  status = USBH_GetDescriptor(pdev, 
                              phost,
                              USB_REQ_RECIPIENT_INTERFACE
                                | USB_REQ_TYPE_STANDARD,                                  
                                USB_DESC_HID,
                                pdev->host.Rx_Buffer,
                                length);
 
  return status;
}


//--------------------------------------------------------------
static USBH_Status USBH_Set_Idle (USB_OTG_CORE_HANDLE *pdev,
                                  USBH_HOST *phost,
                                  uint8_t duration,
                                  uint8_t reportId)
{
  
  phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE |\
    USB_REQ_TYPE_CLASS;
  
  
  phost->Control.setup.b.bRequest = USB_HID_SET_IDLE;
  phost->Control.setup.b.wValue.w = (duration << 8 ) | reportId;
  
  phost->Control.setup.b.wIndex.w = 0;
  phost->Control.setup.b.wLength.w = 0;
  
  return USBH_CtlReq(pdev, phost, 0 , 0 );
}


//--------------------------------------------------------------
USBH_Status USBH_Set_Report (USB_OTG_CORE_HANDLE *pdev, 
                                 USBH_HOST *phost,
                                    uint8_t reportType,
                                    uint8_t reportId,
                                    uint8_t reportLen,
                                    uint8_t* reportBuff)
{
  
  phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE |\
    USB_REQ_TYPE_CLASS;
  
  
  phost->Control.setup.b.bRequest = USB_HID_SET_REPORT;
  phost->Control.setup.b.wValue.w = (reportType << 8 ) | reportId;
  
  phost->Control.setup.b.wIndex.w = 0;
  phost->Control.setup.b.wLength.w = reportLen;
  
  return USBH_CtlReq(pdev, phost, reportBuff , reportLen );
}


//--------------------------------------------------------------
static USBH_Status USBH_Set_Protocol(USB_OTG_CORE_HANDLE *pdev,
                                     USBH_HOST *phost,
                                     uint8_t protocol)
{
  
  
  phost->Control.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE |\
    USB_REQ_TYPE_CLASS;
  
  
  phost->Control.setup.b.bRequest = USB_HID_SET_PROTOCOL;
  
  if(protocol != 0)
  {
    /* Boot Protocol */
    phost->Control.setup.b.wValue.w = 0;
  }
  else
  {
    /*Report Protocol*/
    phost->Control.setup.b.wValue.w = 1;
  }
  
  phost->Control.setup.b.wIndex.w = 0;
  phost->Control.setup.b.wLength.w = 0;
  
  return USBH_CtlReq(pdev, phost, 0 , 0 );
  
}


//--------------------------------------------------------------
static void  USBH_ParseHIDDesc (USBH_HIDDesc_TypeDef *desc, uint8_t *buf)
{
  
  desc->bLength                  = *(uint8_t  *) (buf + 0);
  desc->bDescriptorType          = *(uint8_t  *) (buf + 1);
  desc->bcdHID                   =  LE16  (buf + 2);
  desc->bCountryCode             = *(uint8_t  *) (buf + 4);
  desc->bNumDescriptors          = *(uint8_t  *) (buf + 5);
  desc->bReportDescriptorType    = *(uint8_t  *) (buf + 6);
  desc->wItemLength              =  LE16  (buf + 7);
  
} 

