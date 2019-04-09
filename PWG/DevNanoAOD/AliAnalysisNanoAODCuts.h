#ifndef _ALIANALYSISNANOAODCUTSANDSETTERS_H_
#define _ALIANALYSISNANOAODCUTSANDSETTERS_H_

#include "AliAnalysisCuts.h"
#include "AliNanoAODCustomSetter.h"
#include "AliAnalysisUtils.h"
#include "AliEventCuts.h"
#include <map>

class AliEventCuts;

class AliAnalysisNanoAODTrackCuts : public AliAnalysisCuts
{
public:
  AliAnalysisNanoAODTrackCuts();
  virtual ~AliAnalysisNanoAODTrackCuts()  {}
  virtual Bool_t IsSelected(TObject* obj); // TObject should be an AliAODTrack
  virtual Bool_t IsSelected(TList*   /* list */ ) { return kTRUE; }
  UInt_t GetBitMask() { return fBitMask; }
  void  SetBitMask (UInt_t var) { fBitMask = var;}
  Float_t GetMinPt() { return fMinPt; }
  void  SetMinPt (Float_t var) { fMinPt = var;}
  Float_t GetMaxEta() { return fMaxEta; }
  void  SetMaxEta (Float_t var) { fMaxEta = var;}

private:
  UInt_t fBitMask; // Only AOD tracks matching this bit mask are accepted
  Float_t fMinPt; // miminum pt of the tracks
  Float_t fMaxEta; // MaxEta

  ClassDef(AliAnalysisNanoAODTrackCuts,1); // track cut object for nano AOD filtering
};

class AliAnalysisNanoAODV0Cuts : public AliAnalysisCuts
{
public:
  AliAnalysisNanoAODV0Cuts();
  virtual ~AliAnalysisNanoAODV0Cuts() {}
  virtual Bool_t IsSelected(TObject* obj);  // TObject should be an AliAODv0
  virtual Bool_t IsSelected(TList*   /* list */ ) { return kTRUE; }

  void SetOnFlyStatus(Bool_t flyStat)                { fSelectOnFly = true; fOnFlyStatus = flyStat; }
  void Setv0pTMin(Float_t pTMin)                     { fv0pTMin = pTMin;  }
  void Setv0EtaMax(Float_t EtaMax)                   { fv0EtaMax = EtaMax; }
  void SetTransverseRadius(Float_t min, Float_t max) { fTransverseRadiusMin = min; fTransverseRadiusMax = max; }
  void SetCPAMin(Float_t CPAMin)                     { fCPAMin = CPAMin; }
  void SetMaxDCADaughtersToV0Vtx(Float_t MaxDCA)     { fDCADaugv0VtxMax = MaxDCA; }
  void SetMinDCADaughtersToPrimVtx(Float_t MinDCA)   { fDCADaugPrimVtxMin = MinDCA; }
  void SetDaughterEtaMax(Float_t EtaMax)             { fDaughEtaMax = EtaMax; }
  void SetMinClsTPCDaughters(int minCls)             { fDaugMinClsTPC = minCls; }
  void SetLambdaDaugnSigTPCMax(Float_t maxnSig)      { fLambdaDaugnSigTPCMax = maxnSig; }
  void SetRequireTimingDaughters(Bool_t require)     { fCheckDaughterPileup = require; }
  
private:
  Bool_t fSelectOnFly;
  Bool_t fOnFlyStatus;
  Float_t fv0pTMin;
  Float_t fv0EtaMax;
  Float_t fTransverseRadiusMin;
  Float_t fTransverseRadiusMax;
  Float_t fCPAMin;
  Float_t fDCADaugv0VtxMax;
  Float_t fDCADaugPrimVtxMin;
  Float_t fDaughEtaMax;
  Int_t fDaugMinClsTPC;
  Float_t fLambdaDaugnSigTPCMax;
  Bool_t fCheckDaughterPileup;

  ClassDef(AliAnalysisNanoAODV0Cuts, 1); // track cut object for nano AOD filtering
};

class AliAnalysisNanoAODEventCuts : public AliAnalysisCuts
{
public:
  AliAnalysisNanoAODEventCuts();
  virtual ~AliAnalysisNanoAODEventCuts() {}
  virtual Bool_t IsSelected(TObject* obj); // TObject should be an AliAODEvent
  virtual Bool_t IsSelected(TList*   /* list */ ) { return kTRUE; }
  
  void SetMultiplicityRange(AliAnalysisCuts* cutObject, Int_t minMultiplicity, Int_t maxMultiplicity) { fTrackCut = cutObject; fMinMultiplicity = minMultiplicity; fMaxMultiplicity = maxMultiplicity; }
  AliEventCuts& GetAliEventCuts() { return fEventCuts; }
  
private:
  AliAnalysisCuts* fTrackCut; // track cut object for multiplicity cut
  Int_t fMinMultiplicity;   // minimum number of tracks to accept this event
  Int_t fMaxMultiplicity;   // maximal number of tracks to accept this event
  
  AliEventCuts fEventCuts; // AliEventCut object for Run 2
  
  ClassDef(AliAnalysisNanoAODEventCuts, 3); // event cut object for nano AOD filtering
};

class AliNanoAODSimpleSetter : public AliNanoAODCustomSetter
{
public:
  AliNanoAODSimpleSetter() : fInitialized(kFALSE), fMultMap() {;}
  virtual ~AliNanoAODSimpleSetter(){;}

  virtual void SetNanoAODHeader(const AliAODEvent * event   , AliNanoAODHeader * head ,TString varListHeader  );
  virtual void SetNanoAODTrack (const AliAODTrack * /*aodTrack*/, AliNanoAODTrack * /*spTrack*/);
  
protected:
  void Init(AliNanoAODHeader* head, TString varListHeader);
  
  Bool_t fInitialized;
  std::map<TString,int> fMultMap;

  ClassDef(AliNanoAODSimpleSetter, 2)

};

#endif /* _ALIANALYSISNANOAODCUTSANDSETTERS_H_ */
