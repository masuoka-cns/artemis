/* $Id:$ */
/**
 * @file   TCatEventCollection.h
 * @date   Created : Apr 26, 2012 23:26:19 JST
 *   Last Modified : Feb 02, 2013 22:01:51 JST
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *  
 *  
 *    Copyright (C)2012
 */
#ifndef TCATEVENTCOLLECTION_H
#define TCATEVENTCOLLECTION_H

#include <TTree.h>
#include <TFile.h>
#include <TClonesArray.h>

class TCatEventCollection  {

public:
   static const TString kDefaultOutputName;

   TCatEventCollection();

   virtual ~TCatEventCollection();

   virtual void     Add(TNamed* obj, Bool_t isPassive = kTRUE);
   virtual void     Add(TClonesArray* obj, Bool_t isPassive = kTRUE);
   virtual void     Add(TList* list, Bool_t isPassive = kTRUE);
   virtual TObject* Get(const char* name);
   virtual void     Init(const char *filename = "",const char *opt = "CREATE");

   // issue #628
   // added to remap address to the branch after TTre::Draw() method called.
   virtual void     RemapBranch();

   virtual void     ResetBranch();


   virtual void CreateOutput(const char *name, const char* title);
   virtual void Fill() { if (fOutputTree) fOutputTree->Fill(); }

   virtual const char* GetPath() {
      if (fOutputFile) {
         return fOutputFile->GetPath();
      } 
      return 0;
   }

   virtual TDirectory* GetDir() { return fOutputFile; }
   
   virtual void cd() { if (fOutputFile) fOutputFile->cd(); }

protected:
   TList *fObjects;
   TList *fOutputObjects;
   TTree *fOutputTree;
   TFile *fOutputFile;
   TString fOutputFileName;
};


#endif // end of #ifdef TCATEVENTCOLLECTION_H
