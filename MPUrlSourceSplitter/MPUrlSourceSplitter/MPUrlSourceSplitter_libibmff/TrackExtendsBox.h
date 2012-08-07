/*
    Copyright (C) 2007-2010 Team MediaPortal
    http://www.team-mediaportal.com

    This file is part of MediaPortal 2

    MediaPortal 2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MediaPortal 2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MediaPortal 2.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifndef __TRACK_EXTENDS_BOX_DEFINED
#define __TRACK_EXTENDS_BOX_DEFINED

#include "FullBox.h"

#define TRACK_EXTENDS_BOX_TYPE                                                L"trex"

class CTrackExtendsBox :
  public CFullBox
{
public:
  // initializes a new instance of CTrackExtendsBox class
  CTrackExtendsBox(void);

  // destructor
  virtual ~CTrackExtendsBox(void);

  /* get methods */

  // gets whole box into buffer
  // @param buffer : the buffer for box data
  // @param length : the length of buffer for data
  // @return : true if all data were successfully stored into buffer, false otherwise
  virtual bool GetBox(uint8_t **buffer, uint32_t *length);

  // the track; this shall be the track ID of a track in the Movie Box
  virtual uint32_t GetTrackId(void);

  // default sample description index for track fragments
  virtual uint32_t GetDefaultSampleDescriptionIndex(void);

  // default sample duration for track fragments
  virtual uint32_t GetDefaultSampleDuration(void);

  // default sample size for track fragments
  virtual uint32_t GetDefaultSampleSize(void);

  // default sample flags for track fragments
  virtual uint32_t GetDefaultSampleFlags(void);

  /* set methods */

  /* other methods */

  // parses data in buffer
  // @param buffer : buffer with box data for parsing
  // @param length : the length of data in buffer
  // @return : true if parsed successfully, false otherwise
  virtual bool Parse(const uint8_t *buffer, uint32_t length);

  // gets box data in human readable format
  // @param indent : string to insert before each line
  // @return : box data in human readable format or NULL if error
  virtual wchar_t *GetParsedHumanReadable(const wchar_t *indent);

protected:

  /*

  The sample flags field in sample fragments (defaultSampleFlags here and in a Track Fragment Header
  Box, and sampleFlags and firstSampleFlags in a Track Fragment Run Box) is coded as a 32-bit
  value. It has the following structure:

  bit(6) reserved=0;
  unsigned int(2) sample_depends_on;
  unsigned int(2) sample_is_depended_on;
  unsigned int(2) sample_has_redundancy;
  bit(3) sample_padding_value;
  bit(1) sample_is_difference_sample;
  // i.e. when 1 signals a non-key or non-sync sample
  unsigned int(16) sample_degradation_priority;

  The sample_depends_on, sample_is_depended_on and sample_has_redundancy values are defined
  as documented in the Independent and Disposable Samples Box.

  The sample_padding_value is defined as for the padding bits table. The
  sample_degradation_priority is defined as for the degradation priority table.

  */

  // the track; this shall be the track ID of a track in the Movie Box
  uint32_t trackId;

  // default sample description index for track fragments
  uint32_t defaultSampleDescriptionIndex;

  // default sample duration for track fragments
  uint32_t defaultSampleDuration;

  // default sample size for track fragments
  uint32_t defaultSampleSize;

  // default sample flags for track fragments
  uint32_t defaultSampleFlags;

  // gets box size added to size
  // method is called to determine whole box size for storing box into buffer
  // @param size : the size of box calling this method
  // @return : size of box 
  virtual uint64_t GetBoxSize(uint64_t size);

  // parses data in buffer
  // @param buffer : buffer with box data for parsing
  // @param length : the length of data in buffer
  // @param processAdditionalBoxes : specifies if additional boxes have to be processed
  // @return : true if parsed successfully, false otherwise
  virtual bool ParseInternal(const unsigned char *buffer, uint32_t length, bool processAdditionalBoxes);
};

#endif