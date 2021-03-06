/*****************************************************************************
*                                                                            *
*  OpenNI 2.x Alpha                                                          *
*  Copyright (C) 2012 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of OpenNI.                                              *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*****************************************************************************/
#ifndef _XN_DEVICE_ENUMERATION_H_
#define _XN_DEVICE_ENUMERATION_H_

#include <XnStringsHash.h>
#include <XnEvent.h>
#include <XnArray.h>
#include <OniCTypes.h>
#include <XnUSB.h>

class XnDeviceEnumeration
{
public:
	typedef xnl::Event1Arg<const OniDeviceInfo&> DeviceConnectivityEvent;

	static XnStatus Initialize();
	static void Shutdown();

	static OniDeviceInfo* GetDeviceInfo(const XnChar* uri);

	static DeviceConnectivityEvent::Interface& ConnectedEvent() { return ms_connectedEvent; }
	static DeviceConnectivityEvent::Interface& DisconnectedEvent() { return ms_disconnectedEvent; }

	static XnStatus EnumerateSensors(OniDeviceInfo* aDevices, XnUInt32* pnCount);
	static XnStatus IsSensorLowBandwidth(const XnChar* connectionString, XnBool* pbIsLowband);

private:
	typedef xnl::StringsHash<OniDeviceInfo> DevicesHash;

	static void XN_CALLBACK_TYPE OnConnectivityEventCallback(XnUSBEventArgs* pArgs, void* pCookie);
	static void OnConnectivityEvent(const XnChar* uri, XnUSBEventType eventType, XnUInt16 nProductID);

	static XnBool ms_initialized;
	static DeviceConnectivityEvent ms_connectedEvent;
	static DeviceConnectivityEvent ms_disconnectedEvent;

	static XnUInt16 ms_supportedProducts[];
	static XnUInt16 ms_supportedProductsKinect[];
	static XnUInt32 ms_supportedProductsCount;
	static XnUInt32 ms_supportedProductsKinectCount;
	static DevicesHash ms_devices;
	static xnl::Array<XnRegistrationHandle> ms_aRegistrationHandles;
	static XN_CRITICAL_SECTION_HANDLE ms_lock;
};

#endif