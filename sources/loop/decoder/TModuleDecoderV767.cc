/**
 * @file   TModuleDecoderV767.cc
 * @brief  Decorder class for V767
 *
 * @date   Created:       2013-07-23 10:35:05
 *         Last Modified: 2013-07-31 16:25:22
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 * @note   - TRawDataV767 is typedef of TRawDataV1190.
 *         - Trigger timing subtraction, which is included in anapaw decoder,
 *           is not implemented. It should be done in the processor part.
 *         - Can we unify this with V1190 decoder?
 *
 *    Copyright (C) 2013 KAWASE Shoichiro All rights reserved.
 */

#include "TModuleDecoderV767.h"

#include <TObjArray.h>

#include <TRawDataV767.h>

using art::TModuleDecoderV767;
using art::TRawDataV767;

TModuleDecoderV767::TModuleDecoderV767() 
   : TModuleDecoder(kID, TRawDataV767::Class()){
   fHitData = new TObjArray;
}

TModuleDecoderV767::~TModuleDecoderV767() {
   delete fHitData;
}

Int_t TModuleDecoderV767::Decode(char* buffer, const int &size, TObjArray *seg){
   UInt_t *evtData = (unsigned int*) buffer;
   UInt_t  evtSize = size / sizeof(unsigned int);

   UInt_t  headerID, geoID, evtID, channel, idx, measure;
   Bool_t ghf;          // Global Header Flag
   Bool_t isLeadingEdge;

   TRawDataV767 *data;

   ghf = kFALSE;

   /* clear old hits */
   Clear();
   fHitData->Clear();

   /* main decoding routine */
   for (Int_t i = 0; i != evtSize; ++i) {
      headerID = evtData[i] & kHeaderMask;
      switch (headerID) {
	 case kHeader:
	    ghf   = kTRUE;
	    geoID = (evtData[i] & kMaskGeometry)    >> kShiftGeometry;
	    evtID = (evtData[i] & kMaskEventNumber) >> kShiftEventNumber;
	    break;

	 case kMeasure:
	    channel       =   (evtData[i] & kMaskChannel)  >> kShiftChannel;
	    isLeadingEdge = !((evtData[i] & kMaskEdgeType) >> kShiftEdgeType);
	    measure       =   (evtData[i] & kMaskMeasure)  >> kShiftMeasure;
	    idx           = geoID * 128 + channel;
	    
	    // check if the data object exists
	    if (fHitData->GetEntriesFast() <= idx || !fHitData->At(idx)) {
	       // if no data available, create one
	       TObject *obj = New();
	       ((TRawDataV767*)obj)->SetSegInfo(seg->GetUniqueID(),
						 geoID,channel);
	       fHitData->AddAtAndExpand(obj,idx);
	       seg->Add(obj);
	    }

	    data = (TRawDataV767*)fHitData->At(idx);

	    if (isLeadingEdge) {
	       data->SetLeading(measure);
	    } else {
	       data->SetTrailing(measure);
	       fHitData->AddAt(NULL,idx);
	    }
	    break;

	 case kError:
	    printf("V767 [TDC Error] : evtData[%d] = 0x%08x\n",
		   i, evtData[i]);
	    break;

	 case kEOB:
	    ghf = kFALSE;
	    break;

	 default:
	    break;
      }
   }

   return 0;
}


