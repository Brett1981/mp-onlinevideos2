/*
 *      Copyright (C) 2012-2013 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include "Stdafx.h"
#include "ManagedDemuxPacketHelper.h"

#ifdef _WIN32
#include <windows.h>
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

using namespace std;
using namespace System;

extern "C"
{
  DLLEXPORT void* INPUTSTREAM_register_me(void *hdl)
  {
    return (void*)1;
  }

  DLLEXPORT void INPUTSTREAM_unregister_me(void *hdl, void* cb)
  {
  }

  DLLEXPORT DemuxPacket* INPUTSTREAM_allocate_demux_packet(void *hdl, void* cb, int iDataSize)
  {
    return CManagedDemuxPacketHelper::AllocateDemuxPacket(iDataSize);
  }

  DLLEXPORT void INPUTSTREAM_free_demux_packet(void *hdl, void* cb, DemuxPacket* pPacket)
  {
    CManagedDemuxPacketHelper::FreeDemuxPacket(pPacket);
  }
};
