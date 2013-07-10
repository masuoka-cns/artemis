/* $Id:$ */
/**
 * @file   TEventCollection.cc
 * @date   Created : Jul 10, 2013 17:10:20 JST
 *   Last Modified : 
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *  
 *  
 *    Copyright (C)2013
 */
#include "TEventCollection.h"

art::TEventCollection::TEventCollection()
{
}
art::TEventCollection::~TEventCollection()
{
}


void   art::TEventCollection::Add(const char* name, TObject* obj, Bool_t isPassive)
{
   fObjects->Add(new TEventObject(name,obj,isPassive));
}

art::TEventObject* art::TEventCollection::Get(const char* name)
{
   return (TEventObject*) fObjects->FindObject(name);
}
