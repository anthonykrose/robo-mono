#include "Analyze_eet.hh"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"
#include "TMVA/Types.h"

using namespace std;

ClassImp(Analyze_eet)

//--------------------------------- Make Cuts
//If the candidate passes, returns (1,100)
//If it doesn't, returns (0,#FailedCut)
pair<bool,int> Analyze_eet::makeCuts(int tauNum, int e1Num, int e2Num, int tauSS, int tauOS, TMVA::Reader & theReader){
  pair<bool,int> cutResult;	

  //---------- Require Trigger -------------//
  // if((*HMT).eTauTauTriggerBit == 0 && theCuts[0][0] == 1) {cutResult = make_pair(0,0); return cutResult;}

  //Which trigger to use? For now leave single e trigger

  //---------- Require Trigger -------------//
  if((*HMT).eTriggerBit == 0 && theCuts[0][0] == 1) {cutResult = make_pair(0,0); return cutResult;}

  //---------- Electron 1 TheCuts ------------//
  //Cut 1: Electron 1 Pt
  if((*(*HMT).elecPt)[e1Num] < theCuts[1][0]) {cutResult = make_pair(0,1); return cutResult;}

  //Cut 2: Electron 1 Eta + Crack Cut
  if(TMath::Abs((*(*HMT).elecEta)[e1Num]) > theCuts[2][0]) {cutResult = make_pair(0,2); return cutResult;}    

  //Cut 3: Electron 1 MVA ID
  //----Loose  
  if(theCuts[3][0]==1){
    if((*(*HMT).elecMVAID)[e1Num]<0.905) {cutResult = make_pair(0,3); return cutResult;}
    if(((*(*HMT).elecMVAID)[e1Num]<0.955&&TMath::Abs((*(*HMT).elecEta)[e1Num])>=0.8&&TMath::Abs((*(*HMT).elecEta)[e1Num])<1.479)) {cutResult = make_pair(0,3); return cutResult;}
    if(((*(*HMT).elecMVAID)[e1Num]<0.975&&TMath::Abs((*(*HMT).elecEta)[e1Num])>=1.479)) {cutResult = make_pair(0,3); return cutResult;}
  }
  //----Tight
  if(theCuts[3][0]==3){
    if((*(*HMT).elecMVAID)[e1Num]<0.925) {cutResult = make_pair(0,3); return cutResult;}
    if(((*(*HMT).elecMVAID)[e1Num]<0.975&&TMath::Abs((*(*HMT).elecEta)[e1Num])>=0.8&&TMath::Abs((*(*HMT).elecEta)[e1Num])<1.479)) {cutResult = make_pair(0,3); return cutResult;}
    if(((*(*HMT).elecMVAID)[e1Num]<0.985&&TMath::Abs((*(*HMT).elecEta)[e1Num])>=1.479)) {cutResult = make_pair(0,3); return cutResult;}
  }

  //Cut 4: Electron 1 Relative Isolation
  //----Tight
  if(theCuts[4][0]!=0){
    if((*(*HMT).elecRelIso)[e1Num]>0.15&&TMath::Abs((*(*HMT).elecEta)[e1Num])<=1.479) {cutResult = make_pair(0,4); return cutResult;}
    //if((*(*HMT).elecRelIso)[e1Num]>0.10&&TMath::Abs((*(*HMT).elecEta)[e1Num])<=1.479) {cutResult = make_pair(0,4); return cutResult;}
    if((*(*HMT).elecRelIso)[e1Num]>0.10&&TMath::Abs((*(*HMT).elecEta)[e1Num])>1.479) {cutResult = make_pair(0,4); return cutResult;}
  }

  //Cut 5: Electron XY Vertex
  if((*(*HMT).elecDxyVtx)[e1Num]>theCuts[5][0]) {cutResult = make_pair(0,5); return cutResult;}

  //Cut 6: Electron Z Vertex
  if((*(*HMT).elecDzVtx)[e1Num]>theCuts[6][0]) {cutResult = make_pair(0,6); return cutResult;}



  //---------- Electron 2 TheCuts ------------//
  //Cut 7: Electron 2 Pt
  if((*(*HMT).elecPt)[e2Num] < theCuts[7][0]) {cutResult = make_pair(0,7); return cutResult;}

  //Cut 8: Electron 2 Eta + Crack Cut
  if(TMath::Abs((*(*HMT).elecEta)[e2Num]) > theCuts[8][0]) {cutResult = make_pair(0,8); return cutResult;}    

  //Cut 9: Electron 2 MVA ID
  //----Loose  
  if(theCuts[9][0]==1){
    if((*(*HMT).elecMVAID)[e2Num]<0.905) {cutResult = make_pair(0,9); return cutResult;}
    if(((*(*HMT).elecMVAID)[e2Num]<0.955&&TMath::Abs((*(*HMT).elecEta)[e2Num])>=0.8&&TMath::Abs((*(*HMT).elecEta)[e2Num])<1.479)) {cutResult = make_pair(0,9); return cutResult;}
    if(((*(*HMT).elecMVAID)[e2Num]<0.975&&TMath::Abs((*(*HMT).elecEta)[e2Num])>=1.479)) {cutResult = make_pair(0,9); return cutResult;}
  }
  //----Tight
  if(theCuts[9][0]==3){
    if((*(*HMT).elecMVAID)[e2Num]<0.925) {cutResult = make_pair(0,9); return cutResult;}
    if(((*(*HMT).elecMVAID)[e2Num]<0.975&&TMath::Abs((*(*HMT).elecEta)[e2Num])>=0.8&&TMath::Abs((*(*HMT).elecEta)[e2Num])<1.479)) {cutResult = make_pair(0,9); return cutResult;}
    if(((*(*HMT).elecMVAID)[e2Num]<0.985&&TMath::Abs((*(*HMT).elecEta)[e2Num])>=1.479)) {cutResult = make_pair(0,9); return cutResult;}
  }

  //Cut 10: Electron 2 Relative Isolation
  //----Tight
  if(theCuts[10][0]!=0){
    if((*(*HMT).elecRelIso)[e2Num]>0.15&&TMath::Abs((*(*HMT).elecEta)[e2Num])<=1.479) {cutResult = make_pair(0,10); return cutResult;}
    //if((*(*HMT).elecRelIso)[e2Num]>0.10&&TMath::Abs((*(*HMT).elecEta)[e2Num])<=1.479) {cutResult = make_pair(0,10); return cutResult;}
    if((*(*HMT).elecRelIso)[e2Num]>0.10&&TMath::Abs((*(*HMT).elecEta)[e2Num])>1.479) {cutResult = make_pair(0,10); return cutResult;}
  }

  //Cut 11: Electron 2 XY Vertex
  if((*(*HMT).elecDxyVtx)[e2Num]>theCuts[11][0]) {cutResult = make_pair(0,11); return cutResult;}

  //Cut 12: Electron 2 Z Vertex
  if((*(*HMT).elecDzVtx)[e2Num]>theCuts[12][0]) {cutResult = make_pair(0,12); return cutResult;}


  //---------- Tau Cuts ------------//
  //Cut 13: Lead Tau Pt
  if((*(*HMT).tauPt)[tauNum] < theCuts[13][0]) {cutResult = make_pair(0,13); return cutResult;}

  //Cut 14: Lead Tau Eta
  if(TMath::Abs((*(*HMT).tauEta)[tauNum]) > theCuts[14][0]) {cutResult = make_pair(0,14); return cutResult;}

  //Cut 15: Lead Tau Decay Mode Finding
  if((*(*HMT).tauIdByDecayModeFinding)[tauNum] < 1 && theCuts[15][0]) {cutResult = make_pair(0,15); return cutResult;}

  //Cut 16: Lead Tau Isolation

  if(theCuts[16][0]==1&&(*(*HMT).tauId3HitLooseIsolationDB)[tauNum] < 1) {cutResult = make_pair(0,16); return cutResult;}
  if(theCuts[16][0]==2&&(*(*HMT).tauId3HitMediumIsolationDB)[tauNum] < 1) {cutResult = make_pair(0,16); return cutResult;}
  if(theCuts[16][0]==3&&(*(*HMT).tauId3HitTightIsolationDB)[tauNum] < 1) {cutResult = make_pair(0,16); return cutResult;}


  // if(theCuts[16][0]==1&&(*(*HMT).tauIdByLooseCombinedIsolationDBSumPtCorr)[tauNum] < 1) {cutResult = make_pair(0,16); return cutResult;}
  // if(theCuts[16][0]==2&&(*(*HMT).tauIdByMediumCombinedIsolationDBSumPtCorr)[tauNum] < 1) {cutResult = make_pair(0,16); return cutResult;}
  // if(theCuts[16][0]==3&&(*(*HMT).tauIdByTightCombinedIsolationDBSumPtCorr)[tauNum] < 1) {cutResult = make_pair(0,16); return cutResult;}

  //Cut 17: Lead Tau Muon Rejection
  if(theCuts[17][0]==1&&(*(*HMT).tauIdByLooseMuonRejection)[tauNum] < 1) {cutResult = make_pair(0,17); return cutResult;}
  if(theCuts[17][0]==3&&(*(*HMT).tauIdByTightMuonRejection)[tauNum] < 1) {cutResult = make_pair(0,17); return cutResult;}

  //Cut 18: Lead Tau Electron Rejection  
  // if(theCuts[18][0]==1&&(*(*HMT).tauIdByLooseElectronRejection)[tauNum] < 1) {cutResult = make_pair(0,18); return cutResult;}
  // if(theCuts[18][0]==2&&(*(*HMT).tauIdByMediumElectronRejection)[tauNum] < 1) {cutResult = make_pair(0,18); return cutResult;}
  // if(theCuts[18][0]==3&&(*(*HMT).tauIdByTightElectronRejection)[tauNum] < 1) {cutResult = make_pair(0,18); return cutResult;}

  if(theCuts[18][0]==1&&(*(*HMT).tauIdByMVA3LooseElectronRejection)[tauNum] < 1) {cutResult = make_pair(0,18); return cutResult;}
  if(theCuts[18][0]==2&&(*(*HMT).tauIdByMVA3MediumElectronRejection)[tauNum] < 1) {cutResult = make_pair(0,18); return cutResult;}
  if(theCuts[18][0]==3&&(*(*HMT).tauIdByMVA3TightElectronRejection)[tauNum] < 1) {cutResult = make_pair(0,18); return cutResult;}


  //Cut 19: Lead Tau Z Position
  //if(TMath::Abs((*(*HMT).tauLeadChargedCandDzVtx)[tauNum]-(*(*HMT).elecDzVtx)[tauNum])>theCuts[19][0]) {cutResult = make_pair(0,19); return cutResult;}
  if(TMath::Abs((*(*HMT).tauLeadChargedCandDzVtx)[tauNum])>theCuts[19][0]) {cutResult = make_pair(0,19); return cutResult;}

  //Cut 20 dR(electron 1,tau)  
  if(dR(elecs[e1Num].Eta(),elecs[e1Num].Phi(),taus[tauNum].Eta(),taus[tauNum].Phi())<theCuts[20][0]) {cutResult = make_pair(0,20); return cutResult;}

  //Cut 21: dR(electron 1, electron 2)  
  if(dR(elecs[e1Num].Eta(),elecs[e1Num].Phi(),elecs[e2Num].Eta(),elecs[e2Num].Phi())<theCuts[21][0]) {cutResult = make_pair(0,21); return cutResult;}

  //Cut 22: dR(electron 2,tau)  
  if(dR(elecs[e2Num].Eta(),elecs[e2Num].Phi(),taus[tauNum].Eta(),taus[tauNum].Phi())<theCuts[22][0]) {cutResult = make_pair(0,22); return cutResult;}

  //Cut 23: Opposite Sign Electrons  
  if(theCuts[23][0]&&(*(*HMT).elecCharge)[e1Num]*(*(*HMT).elecCharge)[e2Num] >= 0) {cutResult = make_pair(0,23); return cutResult;}


  for(int numJet = 0; numJet<(*(*HMT).jetCombSecVtxBTag).size(); numJet++){
    if((*(*HMT).jetPt)[0][numJet] < theCuts[24][0]) continue;
    if(fabs((*(*HMT).jetEta)[0][numJet]) > theCuts[24][1]) continue;
//     if((*(*HMT).jetPUIdLoose)[0][numJet] < theCuts[24][2]) continue;                                                                          
    if((*(*HMT).jetCombSecVtxBTag)[numJet] > theCuts[24][3]) {cutResult = make_pair(0,24); return cutResult;}
  }



  //Cut 24: B-Veto
  // if(theCuts[24][0]==1&&(*HMT).nBtagsCombSecVtxLoose!=0) {cutResult = make_pair(0,24); return cutResult;}  	        
  // if(theCuts[24][0]==2&&(*HMT).nBtagsCombSecVtxMedium!=0) {cutResult = make_pair(0,24); return cutResult;}  	        //2012 B-Tag Recommendation
  // if(theCuts[24][0]==3&&(*HMT).nBtagsCombSecVtxTight!=0) {cutResult = make_pair(0,24); return cutResult;}  	        
  //Cut 25: MET Cut
  if((*HMT).MEtMVA<theCuts[25][0]) {cutResult = make_pair(0,25); return cutResult;}

  //-------------------------------------//
  //------- Analysis Overlap Veto -------//
  //-------------------------------------//
  //Cut 26: Mt(e,MET) Cut (analysis overlap cut)
  if(transverseMass(elecs[e1Num],met)<theCuts[26][0]) {cutResult = make_pair(0,26); return cutResult;}

  TLorentzVector ElecElec;
  ElecElec = elecs[e1Num]+elecs[e2Num];
  
  if((*(*HMT).elecCharge)[e1Num]*(*(*HMT).elecCharge)[e2Num] < 0){
    if (ElecElec.M()>theCuts[27][0] && ElecElec.M()<theCuts[27][1]){
      if ((*HMT).MEtMVA<theCuts[27][2]){
	cutResult = make_pair(0,27); return cutResult;
      }
    }
  }
  if ((*HMT).MEtMVA<theCuts[28][0]){
    if(((transverseMass(elecs[e1Num],met))+(transverseMass(elecs[e2Num],met))+(transverseMass(taus[tauNum],met)))<theCuts[28][1]) {cutResult = make_pair(0,28); return cutResult;}
  }

  mva_Elec1Pt = elecs[e1Num].Pt();
  mva_Elec2Pt = elecs[e2Num].Pt();
  mva_TauPt = taus[tauNum].Pt();
  mva_MET = (*HMT).MEtMVA;
  mva_Mt_Elec1Elec2 = transverseMass(elecs[e2Num],met)+transverseMass(elecs[e1Num],met);
  mva_Mt_Elec1Tau = transverseMass(elecs[e1Num],met)+transverseMass(taus[tauNum],met);
  mva_Mt_Elec2Tau = transverseMass(elecs[e2Num],met)+transverseMass(taus[tauNum],met);
  mva_MaxPt = elecs[e2Num].Pt();
  if (elecs[e1Num].Pt() > mva_MaxPt) mva_MaxPt = elecs[e1Num].Pt();
  if (taus[tauNum].Pt() > mva_MaxPt) mva_MaxPt = taus[tauNum].Pt();

  TLorentzVector Elec1Elec2;
  Elec1Elec2 =elecs[e2Num]+elecs[e1Num];
  mva_MInv_Elec1Elec2 = Elec1Elec2.M();

  TLorentzVector Elec1Tau;
  Elec1Tau =taus[tauNum]+elecs[e1Num];
  mva_MInv_Elec1Tau = Elec1Tau.M();

  TLorentzVector Elec2Tau;
  Elec2Tau =taus[tauNum]+elecs[e2Num];
  mva_MInv_Elec2Tau = Elec2Tau.M();

  TLorentzVector Triplet;
  Triplet =taus[tauNum]+elecs[e2Num]+elecs[e1Num];
  mva_MInv_Triplet = Triplet.M();

  mva_DiElec_eta = Elec1Elec2.Eta();
  mva_DiElec_PtRatio = Elec1Elec2.Pt()/(elecs[e1Num].Pt()+elecs[e2Num].Pt());

  mva_dPhi_elec1 = dPhi(elecs[e1Num].Phi(),(*HMT).MEtMVAPhi);
  mva_dPhi_tau = dPhi(taus[tauNum].Phi(),(*HMT).MEtMVAPhi);
  mva_dPhi_elec2 = dPhi(elecs[e2Num].Phi(),(*HMT).MEtMVAPhi);
	    
  mva_DRElec1Elec2 = dR(elecs[e1Num].Eta(),elecs[e1Num].Phi(),(elecs[e2Num]).Eta(),(elecs[e2Num]).Phi());
  mva_DRElec1Tau = dR(taus[tauNum].Eta(),taus[e1Num].Phi(),(elecs[e1Num]).Eta(),(elecs[e1Num]).Phi());
  mva_DRElec2Tau = dR(elecs[e2Num].Eta(),elecs[e2Num].Phi(),(taus[tauNum]).Eta(),(taus[tauNum]).Phi());
	    

  // double mvaOutput = theReader.EvaluateMVA("MLP");
  double mvaOutput = theReader.EvaluateMVA("KNN");

  if(mvaOutput<theCuts[29][0]) {cutResult = make_pair(0,29); return cutResult;}
  // cout<<"mvaOut = "<<mvaOutput<<" cut 29 = "<<theCuts[29][0]<<endl;



  cutResult = make_pair(1,100);
  return cutResult;

}

void Analyze_eet::printCandidate(int e1Num, int e2Num, int tauNum){
  // TLorentzVector theMET;
  // double metpx = 0;//-elec.Px()-tau1.Px()-tau2.Px();
  // double metpy = 0;//-elec.Py()-tau1.Py()-tau2.Py();

  // TLorentzVector theJET;
  // for(unsigned int jj=0; jj<(*(*HMT).jetPt).size(); jj++){
  //   //if(dR((*(*HMT).jetEta)[jj],(*(*HMT).jetPhi)[jj],elec.Eta(),elec.Phi())<0.2) continue;
  //   //if(dR((*(*HMT).jetEta)[jj],(*(*HMT).jetPhi)[jj],tau1.Eta(),tau1.Phi())<0.2) continue;
  //   //if(dR((*(*HMT).jetEta)[jj],(*(*HMT).jetPhi)[jj],tau2.Eta(),tau2.Phi())<0.2) continue;
    
  //   theJET.SetPtEtaPhiE((*(*HMT).jetPt)[jj],(*(*HMT).jetEta)[jj],(*(*HMT).jetPhi)[jj],(*(*HMT).jetE)[jj]);
  //   metpx = metpx - theJET.Px();
  //   metpy = metpy - theJET.Py();
  // }

  // theMET.SetPxPyPzE(metpx,metpy,0,sqrt(pow(metpx,2)+pow(metpy,2)));

  // cout<<endl<<"Reco Level Stuffs"<<endl;
  // cout<<"------------------------------------------------------------------------------------//"<<endl;
  // cout<<"------------------------------------------------------------------------------------//"<<endl;
  // cout<<"                                   Candidate "<<endl;
  // cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
  // cout<<"Reco Electron 1"<<endl;
  // cout<<"\t\tPt = "<<elecs[e1Num].Pt()<<" Phi = "<<elecs[e1Num].Phi()<<" Eta = "<<elecs[e1Num].Eta()<<endl;
  // cout<<"\t\tPx = "<<elecs[e1Num].Px()<<" Py = "<<elecs[e1Num].Py()<<" Pz = "<<elecs[e1Num].Pz()<<endl;
  // cout<<"Reco Electron 2"<<endl;
  // cout<<"\t\tPt = "<<elecs[e2Num].Pt()<<" Phi = "<<elecs[e2Num].Phi()<<" Eta = "<<elecs[e2Num].Eta()<<endl;
  // cout<<"\t\tPx = "<<elecs[e2Num].Px()<<" Py = "<<elecs[e2Num].Py()<<" Pz = "<<elecs[e2Num].Pz()<<endl;
  // cout<<"Reco Tau"<<endl;
  // cout<<"\t\tPt = "<<taus[tauNum].Pt()<<" Phi = "<<taus[tauNum].Phi()<<" Eta = "<<taus[tauNum].Eta()<<endl;
  // cout<<"\t\tPx = "<<taus[tauNum].Px()<<" Py = "<<taus[tauNum].Py()<<" Pz = "<<taus[tauNum].Pz()<<endl;
  // cout<<"Reco Jets"<<endl;
  // for(unsigned int jj=0;jj<(*(*HMT).jetPt).size();jj++){
  //   cout<<"Jet "<<jj<<"... E = "<<(*(*HMT).jetE)[jj]<<", Pt = "<<(*(*HMT).jetPt)[jj]<<", Eta = "<<(*(*HMT).jetEta)[jj]<<", Phi = "<<(*(*HMT).jetPhi)[jj]<<endl;
  // }
  // cout<<"MET: "<<endl;
  // cout<<"\tMEt Uncorr = "<<(*HMT).MEt<<"\tPhi = "<<(*HMT).MEtPhi<<endl;
  // cout<<"\tMEt Type01 = "<<(*HMT).MEtType01Corrected<<"\tPhi = "<<(*HMT).MEtType01CorrectedPhi<<endl;
  // cout<<"\tMEt MVA    = "<<(*HMT).MEtMVA<<"\tPhi = "<<(*HMT).MEtMVAPhi<<endl;
  // cout<<"\tMEt Candidates = "<<theMET.Pt()<<"\tPhi = "<<theMET.Phi()<<endl;
}


void Analyze_eet::fillHistos(){
}

void Analyze_eet::writeHistos(){
}

void Analyze_eet::makeNewTree(TChain & theTree, TMVA::Reader & theReader, char* outFile, char* outTreeName, char* cutFile, int verbosity){

  TH1F dummyHist("PU","PU",400,0,400);
  setupAnalyzer(theTree, outFile, 1.0, 1, cutFile, 0, 0, 0, 0, dummyHist, verbosity);

  TTree outTree(outTreeName,outTreeName);
  setup_branches_output(outTree,*HMT);

  //----------- Event Loop
  for(int i=0;i<Nentries;i++){


    //Setup objects and parameters for each event
    setupEvent(theTree, i);

    //DO ANY CHECKING OF OBJECTS YOU ARE CONCERNED WITH HAVING HERE
    
    
    //We're interested in analyzing this type of event...
    totAnalyzed++;

    //------------------------------------------ Candidate loop(s) ---------------------------------------//
    for(unsigned int ii=0; ii<taus.size(); ii++){                                              
      for(unsigned int jj=0; jj<elecs.size(); jj++){
	for(unsigned int kk=0; kk<elecs.size(); kk++){
	  if(kk==jj) continue;
	  
	  cutPair=makeCuts(ii,jj,kk,1,1,theReader);

	  //If passed, reset final passed cut to last cut
	  if(cutPair.first) cutPair.second=50;
      
	  //Last passing cut biggest so far?
	  if(cutPair.second-1>lastPassedCut) lastPassedCut = cutPair.second - 1;
      
	  //Didn't pass, move one
	  if(!cutPair.first) continue;	

	  //If you got here, the candidate passed
	  if(!eventPass){
	    //Write the tree
	    if(verbose>0) cout<<"Filling Event "<<i<<"..."<<endl;
	    outTree.Fill();
	    break;
	  }	  
	  eventPass = true;
	}
      }
    }

    //Find the last cut the event passed, if it failed
    if(!eventPass) failedCuts[lastPassedCut+1]++;
  }
  //Make efficiency table?
  printEff(totAnalyzed);

  TFile outputFile(outFile,"RECREATE");
  outTree.Write();
  outputFile.Close();
}

pair<int,double> Analyze_eet::analyze(TChain & theTree, TMVA::Reader & theReader, double scaleFactor, char* outFile, int doCuts, char* cutFile, bool doEff, int doDetail, int doPlots, bool doPU, TH1F* puHisto, int verbosity){

  setupAnalyzer(theTree, outFile, scaleFactor, doCuts, cutFile, doEff, doDetail, doPlots, doPU, *puHisto, verbosity);

  bool madeToCuts=0;

  theReader.AddVariable("Elec1Pt", &mva_Elec1Pt);
  theReader.AddVariable("Elec2Pt", &mva_Elec2Pt);
  theReader.AddVariable("TauPt", &mva_TauPt);
  theReader.AddVariable("MET", &mva_MET);
  theReader.AddVariable("Mt_Elec1Elec2", &mva_Mt_Elec1Elec2);
  theReader.AddVariable("Mt_Elec2Tau", &mva_Mt_Elec2Tau);
  theReader.AddVariable("Mt_Elec1Tau", &mva_Mt_Elec1Tau);
  theReader.AddVariable("MaxPt", &mva_MaxPt);
  theReader.AddVariable("MInv_Elec1Elec2", &mva_MInv_Elec1Elec2);
  theReader.AddVariable("MInv_Elec2Tau", &mva_MInv_Elec2Tau);
  theReader.AddVariable("MInv_Elec1Tau", &mva_MInv_Elec1Tau);
  theReader.AddVariable("MInv_Triplet", &mva_MInv_Triplet);
  theReader.AddVariable("dPhi_elec1",&mva_dPhi_elec1);
  theReader.AddVariable("dPhi_elec2",&mva_dPhi_elec2);
  theReader.AddVariable("dPhi_tau",&mva_dPhi_tau);
  theReader.AddVariable("DiElec_eta",&mva_DiElec_eta);
  theReader.AddVariable("DiElec_PtRatio",&mva_DiElec_PtRatio);
  theReader.AddVariable("DRElec1Elec2",&mva_DRElec1Elec2);
  theReader.AddVariable("DRElec1Tau",&mva_DRElec1Tau);
  theReader.AddVariable("DRElec2Tau",&mva_DRElec2Tau);

    // theReader.BookMVA("MLP", "/uscms_data/d3/arose/CMSSW_5_3_9/src/WHTauTau/GeneralAnalyzer/TMVAClassification_MLP.weights_eet.xml");
    theReader.BookMVA("KNN", "/uscms_data/d3/arose/CMSSW_5_3_9/src/WHTauTau/GeneralAnalyzer/TMVAClassification_KNN.weights_eet_DY.xml");

    

  //----------- Event Loop
  for(int i=0;i<Nentries;i++){

    //Setup the objects and parameters for each event
    setupEvent(theTree, i);

    //Need at least 2 electrons and 1 tau
    if(elecs.size()<2 || taus.size()<1) continue;

    //We're interested in analyzing this type of event...
    totAnalyzed++;

    madeToCuts=0;

    //------------------------------------------ Candidate loop(s) ---------------------------------------//
    for(unsigned int ii=0; ii<taus.size(); ii++){                                              
      for(unsigned int jj=0; jj<elecs.size(); jj++){
	for(unsigned int kk=0; kk<elecs.size(); kk++){
	  
	  if(kk==jj) continue;         //Don't want elec1 = elec2
	  
          int tau12Opp = 0;
          //if(tau12Opp!=1&&tau12Opp!=2) continue;

          int tau12Same = 0;

          madeToCuts = 1;

	  //----------------------- Make Cuts? -------------------------//
	  if(do_cuts!=0){	

	    //CHANGE THIS TO BE COMPATIBLE WITH YOUR makeCuts FUNCTION
	    cutPair=makeCuts(ii,jj,kk,tau12Same,tau12Opp,theReader);

	    //----------- Don't need to change this ------------//
	    //If passed, reset final passed cut to last cut
	    if(cutPair.first) cutPair.second=50;

	    //Last passing cut biggest so far?
	    if(cutPair.second-1>lastPassedCut) lastPassedCut = cutPair.second - 1;
	  
	    //Didn't pass, move one
	    if(!cutPair.first) continue;	
	    //--------------------------------------------------//
	  }



	  //-----------------------------------------------------------//
      
	  //----------------- First Candidate to Pass? ----------------//
	  if(!eventPass){ 								      //Filled Histograms Yet?


	    if(do_pu) pu_rw = getPU();
	    else pu_rw = 1.;
	    if(verbose>0) cout<<(*HMT).TruePU<<" vertices and Prob = "<<pu_rw<<endl;

	    //NEED TO CHANGE THIS TO APPROPRIATE INVARIANT MASS FOR YOU CANDIDATE
	    Minv->Fill(elecs[jj].M(),pu_rw); 

	    dR_elecelec->Fill(elecs[jj].DeltaR(elecs[kk]),pu_rw);

	    EventN->Fill(1.,pu_rw);

	    Tau1Eta->Fill(taus[ii].Eta(),pu_rw);
	    Elec1Eta->Fill(elecs[jj].Eta(),pu_rw);
	    Elec2Eta->Fill(elecs[kk].Eta(),pu_rw);
	    Tau1Pt->Fill(taus[ii].Pt(),pu_rw);
	    Elec1Pt->Fill(elecs[jj].Pt(),pu_rw);
	    Elec2Pt->Fill(elecs[kk].Pt(),pu_rw);

	    double maxPt = 0;
	    if (taus[ii].Pt() > maxPt)maxPt = taus[ii].Pt();
	    if (elecs[jj].Pt() > maxPt)maxPt = elecs[jj].Pt();
	    if (elecs[kk].Pt() > maxPt)maxPt = elecs[kk].Pt();

	    MaxPt->Fill(maxPt,pu_rw);
	    double ht = 0;
	    ht = taus[ii].Pt();
	    ht+= elecs[jj].Pt();
	    ht+= elecs[kk].Pt();

	    double meff = 0;
	    meff = ht + (*HMT).MEtMVA;

	    Ht->Fill(ht,pu_rw);
	    Meff->Fill(meff,pu_rw);
	    MVAMEt->Fill((*HMT).MEtMVA,pu_rw);

	    Mt_elec1->Fill(transverseMass(elecs[jj],met), pu_rw);
	    Mt_elec2->Fill(transverseMass(elecs[kk],met), pu_rw);
	    Mt_tau1->Fill(transverseMass(taus[ii],met), pu_rw);

	    dPhi_tau1->Fill(dPhi(taus[ii].Phi(),(*HMT).MEtMVAPhi));
	    dPhi_elec1->Fill(dPhi(elecs[jj].Phi(),(*HMT).MEtMVAPhi));
	    dPhi_elec2->Fill(dPhi(elecs[kk].Phi(),(*HMT).MEtMVAPhi));

	    TLorentzVector ElecElec;
	    ElecElec = elecs[jj]+elecs[kk];

	    TLorentzVector ElecElec_OS;
	    if((*(*HMT).elecCharge)[kk]*(*(*HMT).elecCharge)[jj] < 0){
	      ElecElec_OS = elecs[jj]+elecs[kk];
	      MInvElecElec_OS->Fill(ElecElec_OS.M(),pu_rw);
	    }
	    TLorentzVector ElecElec_SS;
	    if((*(*HMT).elecCharge)[kk]*(*(*HMT).elecCharge)[jj] > 0){
	      ElecElec_SS = elecs[jj]+elecs[kk];
	      MInvElecElec_SS->Fill(ElecElec_SS.M(),pu_rw);
	    }
	    TLorentzVector Elec1Tau;
	    Elec1Tau = elecs[jj]+taus[ii];
	    TLorentzVector Elec2Tau;
	    Elec2Tau = elecs[kk]+taus[ii];

	    TLorentzVector ElecTau_OS;
	    TLorentzVector ElecTau_SS;
	    TLorentzVector Elec1Tau_OS;
	    TLorentzVector Elec1Tau_SS;
	    TLorentzVector Elec2Tau_OS;
	    TLorentzVector Elec2Tau_SS;

	    bool elec1tauOS = false;
	    bool elec2tauOS = false;
	    bool elec1tauSS = false;
	    bool elec2tauSS = false;

	    if((*(*HMT).elecCharge)[kk]*(*(*HMT).tauCharge)[ii] > 0){
	      ElecTau_SS = elecs[kk]+taus[ii];
	      Elec2Tau_SS = elecs[kk]+taus[ii];
	      elec2tauSS = true;
	    }
	    if((*(*HMT).elecCharge)[jj]*(*(*HMT).tauCharge)[ii] > 0){
	      ElecTau_SS = elecs[jj]+taus[ii];
	      Elec1Tau_SS = elecs[jj]+taus[ii];
 	      elec1tauSS = true;
	    }
	    if((*(*HMT).elecCharge)[kk]*(*(*HMT).tauCharge)[ii] < 0){
	      ElecTau_OS = elecs[kk]+taus[ii];
	      Elec2Tau_OS = elecs[kk]+taus[ii];
 	      elec2tauOS = true;
	    }
	    if((*(*HMT).elecCharge)[jj]*(*(*HMT).tauCharge)[ii] < 0){
	      ElecTau_OS = elecs[jj]+taus[ii];
	      Elec1Tau_OS = elecs[jj]+taus[ii];
 	      elec1tauOS = true;
	    }

	    MInvElecTau_OS->Fill(ElecTau_OS.M(),pu_rw);
	    MInvElecTau_SS->Fill(ElecTau_SS.M(),pu_rw);

	    if (elec1tauOS) MInvElec1Tau_OS->Fill(Elec1Tau_OS.M(),pu_rw);
	    if (elec1tauSS) MInvElec1Tau_SS->Fill(Elec1Tau_SS.M(),pu_rw);
	    if (elec2tauOS) MInvElec2Tau_OS->Fill(Elec2Tau_OS.M(),pu_rw);
	    if (elec2tauSS) MInvElec2Tau_SS->Fill(Elec2Tau_SS.M(),pu_rw);




	    TLorentzVector Triplet;
	    Triplet = elecs[jj]+elecs[kk]+taus[ii];


	    mva_Elec1Pt = elecs[jj].Pt();
	    mva_Elec2Pt = elecs[kk].Pt();
	    mva_TauPt = taus[ii].Pt();
	    mva_MET = (*HMT).MEtMVA;
	    mva_Mt_Elec1Elec2 = transverseMass(elecs[kk],met)+transverseMass(elecs[jj],met);
	    mva_Mt_Elec2Tau = transverseMass(elecs[kk],met)+transverseMass(taus[ii],met);
	    mva_Mt_Elec1Tau = transverseMass(elecs[jj],met)+transverseMass(taus[ii],met);
	    mva_MaxPt = elecs[kk].Pt();
	    if (elecs[jj].Pt() > mva_MaxPt) mva_MaxPt = elecs[jj].Pt();
	    if (taus[ii].Pt() > mva_MaxPt) mva_MaxPt = taus[ii].Pt();

	    TLorentzVector Elec1Elec2;
	    Elec1Elec2 =elecs[kk]+elecs[jj];
	    mva_MInv_Elec1Elec2 = Elec1Elec2.M();

	    mva_MInv_Elec1Tau = Elec1Tau.M();

	    mva_MInv_Elec2Tau = Elec2Tau.M();
	    mva_MInv_Triplet = Triplet.M();


	    mva_dPhi_elec1 = dPhi(elecs[jj].Phi(),(*HMT).MEtMVAPhi);
	    mva_dPhi_tau = dPhi(taus[ii].Phi(),(*HMT).MEtMVAPhi);
	    mva_dPhi_elec2 = dPhi(elecs[kk].Phi(),(*HMT).MEtMVAPhi);
	    
	    mva_DRElec1Elec2 = dR(elecs[jj].Eta(),elecs[jj].Phi(),(elecs[kk]).Eta(),(elecs[kk]).Phi());
	    mva_DRElec1Tau = dR(taus[ii].Eta(),taus[jj].Phi(),(elecs[jj]).Eta(),(elecs[jj]).Phi());
	    mva_DRElec2Tau = dR(elecs[kk].Eta(),elecs[kk].Phi(),(taus[ii]).Eta(),(taus[ii]).Phi());

	    mva_DiElec_eta = Elec1Elec2.Eta();
	    mva_DiElec_PtRatio = Elec1Elec2.Pt()/(elecs[jj].Pt()+elecs[kk].Pt());


	    double mvaOutput = theReader.EvaluateMVA("KNN");

	    //	    double mvaOutput = theReader.EvaluateMVA("MLP");

	    MLP_MVAout->Fill(mvaOutput,pu_rw);
	    KNN_MVAout->Fill(mvaOutput,pu_rw);

	    MInvElecElec->Fill(ElecElec.M(),pu_rw);
	    MInvElec1Tau->Fill(Elec1Tau.M(),pu_rw);
	    MInvElec2Tau->Fill(Elec2Tau.M(),pu_rw);
	    MInvTriplet->Fill(Triplet.M(),pu_rw);
  
	    //ElecElecTau
	    MInvElecElec_vs_MInvElec1Tau->Fill(ElecElec.M(),Elec1Tau.M(),pu_rw);
	    MInvElecElec_vs_MInvElec2Tau->Fill(ElecElec.M(),Elec2Tau.M(),pu_rw);

	    MInvElecElec_vs_MInvElecTau_OS->Fill(ElecElec.M(),ElecTau_OS.M(),pu_rw);
	    MInvElecElec_vs_MInvElecTau_SS->Fill(ElecElec.M(),ElecTau_SS.M(),pu_rw);

	    if (elec1tauOS){
	      MInvElecElec_vs_MInvElec1Tau_OS->Fill(ElecElec.M(),Elec1Tau_OS.M(),pu_rw);
	      MInvTriplet_vs_MInvElec1Tau_OS->Fill(Triplet.M(),Elec1Tau_OS.M(),pu_rw);
	      MInvElec1Tau_OS_vs_dPhi_tau->Fill(Elec1Tau_OS.M(),dPhi(taus[ii].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	      MInvElec1Tau_OS_vs_dPhi_elec1->Fill(Elec1Tau_OS.M(),dPhi(elecs[jj].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	      MInvElec1Tau_OS_vs_dPhi_elec2->Fill(Elec1Tau_OS.M(),dPhi(elecs[kk].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	      MInvElec1Tau_OS_vs_MET->Fill(Elec1Tau_OS.M(),(*HMT).MEtMVA,pu_rw);
	      MInvElec1Tau_OS_vs_HT->Fill(Elec1Tau_OS.M(),ht,pu_rw);
	      MInvElec1Tau_OS_vs_mT_Elec1->Fill(Elec1Tau_OS.M(),transverseMass(elecs[jj],met),pu_rw);
	      MInvElec1Tau_OS_vs_mT_Elec2->Fill(Elec1Tau_OS.M(),transverseMass(elecs[kk],met),pu_rw);
	      MInvElec1Tau_OS_vs_mT_Tau->Fill(Elec1Tau_OS.M(),transverseMass(taus[ii],met),pu_rw);
	    }

	    if (elec1tauSS){
	      MInvElecElec_vs_MInvElec1Tau_SS->Fill(ElecElec.M(),Elec1Tau_SS.M(),pu_rw);
	      MInvTriplet_vs_MInvElec1Tau_SS->Fill(Triplet.M(),Elec1Tau_SS.M(),pu_rw);
	      MInvElec1Tau_SS_vs_dPhi_tau->Fill(Elec1Tau_SS.M(),dPhi(taus[ii].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	      MInvElec1Tau_SS_vs_dPhi_elec1->Fill(Elec1Tau_SS.M(),dPhi(elecs[jj].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	      MInvElec1Tau_SS_vs_dPhi_elec2->Fill(Elec1Tau_SS.M(),dPhi(elecs[kk].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	      MInvElec1Tau_SS_vs_MET->Fill(Elec1Tau_SS.M(),(*HMT).MEtMVA,pu_rw);
	      MInvElec1Tau_SS_vs_HT->Fill(Elec1Tau_SS.M(),ht,pu_rw);
	      MInvElec1Tau_SS_vs_mT_Elec1->Fill(Elec1Tau_SS.M(),transverseMass(elecs[jj],met),pu_rw);
	      MInvElec1Tau_SS_vs_mT_Elec2->Fill(Elec1Tau_SS.M(),transverseMass(elecs[kk],met),pu_rw);
	      MInvElec1Tau_SS_vs_mT_Tau->Fill(Elec1Tau_SS.M(),transverseMass(taus[ii],met),pu_rw);
	    }

	    if (elec2tauOS){
	      MInvElecElec_vs_MInvElec2Tau_OS->Fill(ElecElec.M(),Elec2Tau_OS.M(),pu_rw);
	      MInvTriplet_vs_MInvElec2Tau_OS->Fill(Triplet.M(),Elec2Tau_OS.M(),pu_rw);
	      MInvElec2Tau_OS_vs_dPhi_tau->Fill(Elec2Tau_OS.M(),dPhi(taus[ii].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	      MInvElec2Tau_OS_vs_dPhi_elec1->Fill(Elec2Tau_OS.M(),dPhi(elecs[jj].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	      MInvElec2Tau_OS_vs_dPhi_elec2->Fill(Elec2Tau_OS.M(),dPhi(elecs[kk].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	      MInvElec2Tau_OS_vs_MET->Fill(Elec2Tau_OS.M(),(*HMT).MEtMVA,pu_rw);
	      MInvElec2Tau_OS_vs_HT->Fill(Elec2Tau_OS.M(),ht,pu_rw);
	      MInvElec2Tau_OS_vs_mT_Elec1->Fill(Elec2Tau_OS.M(),transverseMass(elecs[jj],met),pu_rw);
	      MInvElec2Tau_OS_vs_mT_Elec2->Fill(Elec2Tau_OS.M(),transverseMass(elecs[kk],met),pu_rw);
	      MInvElec2Tau_OS_vs_mT_Tau->Fill(Elec2Tau_OS.M(),transverseMass(taus[ii],met),pu_rw);
	    }

	    if (elec2tauSS){
	      MInvElecElec_vs_MInvElec2Tau_SS->Fill(ElecElec.M(),Elec2Tau_SS.M(),pu_rw);
	      MInvTriplet_vs_MInvElec2Tau_SS->Fill(Triplet.M(),Elec2Tau_SS.M(),pu_rw);
	      MInvElec2Tau_SS_vs_dPhi_tau->Fill(Elec2Tau_SS.M(),dPhi(taus[ii].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	      MInvElec2Tau_SS_vs_dPhi_elec1->Fill(Elec2Tau_SS.M(),dPhi(elecs[jj].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	      MInvElec2Tau_SS_vs_dPhi_elec2->Fill(Elec2Tau_SS.M(),dPhi(elecs[kk].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	      MInvElec2Tau_SS_vs_MET->Fill(Elec2Tau_SS.M(),(*HMT).MEtMVA,pu_rw);
	      MInvElec2Tau_SS_vs_HT->Fill(Elec2Tau_SS.M(),ht,pu_rw);
	      MInvElec2Tau_SS_vs_mT_Elec1->Fill(Elec2Tau_SS.M(),transverseMass(elecs[jj],met),pu_rw);
	      MInvElec2Tau_SS_vs_mT_Elec2->Fill(Elec2Tau_SS.M(),transverseMass(elecs[kk],met),pu_rw);
	      MInvElec2Tau_SS_vs_mT_Tau->Fill(Elec2Tau_SS.M(),transverseMass(taus[ii],met),pu_rw);
	    }

	    MInvElecElec_vs_MInvElec1Tau->Fill(ElecElec.M(),Elec1Tau.M(),pu_rw);
	    MInvTriplet_vs_MInvElec1Tau->Fill(Triplet.M(),Elec1Tau.M(),pu_rw);
	    MInvElec1Tau_vs_dPhi_tau->Fill(Elec1Tau.M(),dPhi(taus[ii].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	    MInvElec1Tau_vs_dPhi_elec1->Fill(Elec1Tau.M(),dPhi(elecs[jj].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	    MInvElec1Tau_vs_dPhi_elec2->Fill(Elec1Tau.M(),dPhi(elecs[kk].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	    MInvElec1Tau_vs_MET->Fill(Elec1Tau.M(),(*HMT).MEtMVA,pu_rw);
	    MInvElec1Tau_vs_HT->Fill(Elec1Tau.M(),ht,pu_rw);
	    MInvElec1Tau_vs_mT_Elec1->Fill(Elec1Tau.M(),transverseMass(elecs[jj],met),pu_rw);
	    MInvElec1Tau_vs_mT_Elec2->Fill(Elec1Tau.M(),transverseMass(elecs[kk],met),pu_rw);
	    MInvElec1Tau_vs_mT_Tau->Fill(Elec1Tau.M(),transverseMass(taus[ii],met),pu_rw);

	    MInvElecElec_vs_MInvElec2Tau->Fill(ElecElec.M(),Elec2Tau.M(),pu_rw);
	    MInvTriplet_vs_MInvElec2Tau->Fill(Triplet.M(),Elec2Tau.M(),pu_rw);
	    MInvElec2Tau_vs_dPhi_tau->Fill(Elec2Tau.M(),dPhi(taus[ii].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	    MInvElec2Tau_vs_dPhi_elec1->Fill(Elec2Tau.M(),dPhi(elecs[jj].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	    MInvElec2Tau_vs_dPhi_elec2->Fill(Elec2Tau.M(),dPhi(elecs[kk].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	    MInvElec2Tau_vs_MET->Fill(Elec2Tau.M(),(*HMT).MEtMVA,pu_rw);
	    MInvElec2Tau_vs_HT->Fill(Elec2Tau.M(),ht,pu_rw);
	    MInvElec2Tau_vs_mT_Elec1->Fill(Elec2Tau.M(),transverseMass(elecs[jj],met),pu_rw);
	    MInvElec2Tau_vs_mT_Elec2->Fill(Elec2Tau.M(),transverseMass(elecs[kk],met),pu_rw);
	    MInvElec2Tau_vs_mT_Tau->Fill(Elec2Tau.M(),transverseMass(taus[ii],met),pu_rw);

	    MInvElecElec_vs_dPhi_tau->Fill(ElecElec.M(),dPhi(taus[ii].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	    MInvElecElec_vs_dPhi_elec1->Fill(ElecElec.M(),dPhi(elecs[jj].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	    MInvElecElec_vs_dPhi_elec2->Fill(ElecElec.M(),dPhi(elecs[kk].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	    MInvElecElec_vs_MET->Fill(ElecElec.M(),(*HMT).MEtMVA,pu_rw);
	    MInvElecElec_vs_HT->Fill(ElecElec.M(),ht,pu_rw);
	    MInvElecElec_vs_mT_Elec1->Fill(ElecElec.M(),transverseMass(elecs[jj],met),pu_rw);
	    MInvElecElec_vs_mT_Elec2->Fill(ElecElec.M(),transverseMass(elecs[kk],met),pu_rw);
	    MInvElecElec_vs_mT_Tau->Fill(ElecElec.M(),transverseMass(taus[ii],met),pu_rw);

	    MInvTriplet_vs_MInvElecElec->Fill(Triplet.M(),ElecElec.M(),pu_rw);
	    MInvTriplet_vs_dPhi_tau->Fill(Triplet.M(),dPhi(taus[ii].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	    MInvTriplet_vs_dPhi_elec1->Fill(Triplet.M(),dPhi(elecs[jj].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	    MInvTriplet_vs_dPhi_elec2->Fill(Triplet.M(),dPhi(elecs[kk].Phi(),(*HMT).MEtMVAPhi),pu_rw);
	    MInvTriplet_vs_MET->Fill(Triplet.M(),(*HMT).MEtMVA,pu_rw);
	    MInvTriplet_vs_HT->Fill(Triplet.M(),ht,pu_rw);
	    MInvTriplet_vs_mT_Elec1->Fill(Triplet.M(),transverseMass(elecs[jj],met),pu_rw);
	    MInvTriplet_vs_mT_Elec2->Fill(Triplet.M(),transverseMass(elecs[kk],met),pu_rw);
	    MInvTriplet_vs_mT_Tau->Fill(Triplet.M(),transverseMass(taus[ii],met),pu_rw);


	    Mt_tau1elec1->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	    Mt_tau1elec2->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	    Mt_elec1elec2->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    Mt_tau1elec1elec2->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);

	    Ht_vs_Mt_tau1elec1elec2->Fill(ht,transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    Meff_vs_Mt_tau1elec1elec2->Fill(meff,transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    MVAMEt_vs_Mt_tau1elec1elec2->Fill((*HMT).MEtMVA,transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    MInvElecElec_vs_Mt_tau1elec1elec2->Fill(ElecElec.M(),transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    MInvElec1Tau_vs_Mt_tau1elec1elec2->Fill(Elec1Tau.M(),transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    MInvElec2Tau_vs_Mt_tau1elec1elec2->Fill(Elec2Tau.M(),transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    if (elec1tauOS) MInvElec1Tau_OS_vs_Mt_tau1elec1elec2->Fill(Elec1Tau_OS.M(),transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    if (elec2tauOS) MInvElec2Tau_OS_vs_Mt_tau1elec1elec2->Fill(Elec2Tau_OS.M(),transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    if (elec1tauSS) MInvElec1Tau_SS_vs_Mt_tau1elec1elec2->Fill(Elec1Tau_SS.M(),transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    if (elec2tauSS) MInvElec2Tau_SS_vs_Mt_tau1elec1elec2->Fill(Elec2Tau_SS.M(),transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    MInvTriplet_vs_Mt_tau1elec1elec2->Fill(Triplet.M(),transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);


	    if (elec1tauOS){
	      Mt_tau1elec1_elec1tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      Mt_tau1elec2_elec1tauOS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      Mt_elec1elec2_elec1tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      Mt_tau1elec1elec2_elec1tauOS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    }
	    if (elec1tauSS){
	      Mt_tau1elec1_elec1tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      Mt_tau1elec2_elec1tauSS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      Mt_elec1elec2_elec1tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      Mt_tau1elec1elec2_elec1tauSS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    }
	    if (elec2tauOS){
	      Mt_tau1elec1_elec2tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      Mt_tau1elec2_elec2tauOS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      Mt_elec1elec2_elec2tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      Mt_tau1elec1elec2_elec2tauOS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    }
	    if (elec2tauSS){
	      Mt_tau1elec1_elec2tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      Mt_tau1elec2_elec2tauSS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      Mt_elec1elec2_elec2tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      Mt_tau1elec1elec2_elec2tauSS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	    }

	    if ((*HMT).MEtMVA<60){
	      
	      Mt_tau1elec1_MET60->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      Mt_tau1elec2_MET60->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      Mt_elec1elec2_MET60->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      Mt_tau1elec1elec2_MET60->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);

	      if (elec1tauOS){
	      	Mt_tau1elec1_MET60_elec1tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_tau1elec2_MET60_elec1tauOS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_elec1elec2_MET60_elec1tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      	Mt_tau1elec1elec2_MET60_elec1tauOS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      }
	      if (elec1tauSS){
	      	Mt_tau1elec1_MET60_elec1tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_tau1elec2_MET60_elec1tauSS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_elec1elec2_MET60_elec1tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      	Mt_tau1elec1elec2_MET60_elec1tauSS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      }
	      if (elec2tauOS){
	      	Mt_tau1elec1_MET60_elec2tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_tau1elec2_MET60_elec2tauOS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_elec1elec2_MET60_elec2tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      	Mt_tau1elec1elec2_MET60_elec2tauOS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      }
	      if (elec2tauSS){
	      	Mt_tau1elec1_MET60_elec2tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_tau1elec2_MET60_elec2tauSS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_elec1elec2_MET60_elec2tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      	Mt_tau1elec1elec2_MET60_elec2tauSS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      }

	      Ht_MET60->Fill(ht,pu_rw);
	      Meff_MET60->Fill(meff,pu_rw);
	      MInvElec2Tau_vs_HT_MET60->Fill(Elec2Tau.M(),ht,pu_rw);
	      MInvElecTau_OS_MET60->Fill(ElecTau_OS.M(),pu_rw);
	      MInvElecTau_SS_MET60->Fill(ElecTau_SS.M(),pu_rw);
	      MInvElecElec_MET60->Fill(ElecElec.M(),pu_rw);
	      MInvElec1Tau_MET60->Fill(Elec1Tau.M(),pu_rw);
	      MInvElec2Tau_MET60->Fill(Elec2Tau.M(),pu_rw);
	      if (elec1tauOS) MInvElec1Tau_OS_MET60->Fill(Elec1Tau_OS.M(),pu_rw);
	      if (elec1tauSS) MInvElec1Tau_SS_MET60->Fill(Elec1Tau_SS.M(),pu_rw);
	      if (elec2tauOS) MInvElec2Tau_OS_MET60->Fill(Elec2Tau_OS.M(),pu_rw);
	      if (elec2tauSS) MInvElec2Tau_SS_MET60->Fill(Elec2Tau_SS.M(),pu_rw);
	    }

	    if (ElecElec.M()>80 && ElecElec.M()<100){


	      Mt_tau1elec1_Zmass->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      Mt_tau1elec2_Zmass->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      Mt_elec1elec2_Zmass->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      Mt_tau1elec1elec2_Zmass->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);

	      if (elec1tauOS){
	      	Mt_tau1elec1_Zmass_elec1tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_tau1elec2_Zmass_elec1tauOS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_elec1elec2_Zmass_elec1tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      	Mt_tau1elec1elec2_Zmass_elec1tauOS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      }
	      if (elec1tauSS){
	      	Mt_tau1elec1_Zmass_elec1tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_tau1elec2_Zmass_elec1tauSS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_elec1elec2_Zmass_elec1tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      	Mt_tau1elec1elec2_Zmass_elec1tauSS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      }
	      if (elec2tauOS){
	      	Mt_tau1elec1_Zmass_elec2tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_tau1elec2_Zmass_elec2tauOS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_elec1elec2_Zmass_elec2tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      	Mt_tau1elec1elec2_Zmass_elec2tauOS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      }
	      if (elec2tauSS){
	      	Mt_tau1elec1_Zmass_elec2tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_tau1elec2_Zmass_elec2tauSS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
	      	Mt_elec1elec2_Zmass_elec2tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      	Mt_tau1elec1elec2_Zmass_elec2tauSS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
	      }

	      Ht_Zmass->Fill(ht,pu_rw);
	      Meff_Zmass->Fill(meff,pu_rw);
	      MInvElec2Tau_vs_HT_Zmass->Fill(Elec2Tau.M(),ht,pu_rw);
	      MInvElecTau_OS_Zmass->Fill(ElecTau_OS.M(),pu_rw);
	      MInvElecTau_SS_Zmass->Fill(ElecTau_SS.M(),pu_rw);
	      MInvElecElec_Zmass->Fill(ElecElec.M(),pu_rw);
	      MInvElec1Tau_Zmass->Fill(Elec1Tau.M(),pu_rw);
	      MInvElec2Tau_Zmass->Fill(Elec2Tau.M(),pu_rw);
	      if (elec1tauOS) MInvElec1Tau_OS_Zmass->Fill(Elec1Tau_OS.M(),pu_rw);
	      if (elec1tauSS) MInvElec1Tau_SS_Zmass->Fill(Elec1Tau_SS.M(),pu_rw);
	      if (elec2tauOS) MInvElec2Tau_OS_Zmass->Fill(Elec2Tau_OS.M(),pu_rw);
	      if (elec2tauSS) MInvElec2Tau_SS_Zmass->Fill(Elec2Tau_SS.M(),pu_rw);

	      if ((*HMT).MEtMVA<60){

		Mt_tau1elec1_Zmass_MET60->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
		Mt_tau1elec2_Zmass_MET60->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
		Mt_elec1elec2_Zmass_MET60->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
		Mt_tau1elec1elec2_Zmass_MET60->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);

		if (elec1tauOS){
		  Mt_tau1elec1_Zmass_MET60_elec1tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
		  Mt_tau1elec2_Zmass_MET60_elec1tauOS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
		  Mt_elec1elec2_Zmass_MET60_elec1tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
		  Mt_tau1elec1elec2_Zmass_MET60_elec1tauOS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
		}
		if (elec1tauSS){
		  Mt_tau1elec1_Zmass_MET60_elec1tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
		  Mt_tau1elec2_Zmass_MET60_elec1tauSS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
		  Mt_elec1elec2_Zmass_MET60_elec1tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
		  Mt_tau1elec1elec2_Zmass_MET60_elec1tauSS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
		}
		if (elec2tauOS){
		  Mt_tau1elec1_Zmass_MET60_elec2tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
		  Mt_tau1elec2_Zmass_MET60_elec2tauOS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
		  Mt_elec1elec2_Zmass_MET60_elec2tauOS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
		  Mt_tau1elec1elec2_Zmass_MET60_elec2tauOS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
		}
		if (elec2tauSS){
		  Mt_tau1elec1_Zmass_MET60_elec2tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(taus[ii],met), pu_rw);
		  Mt_tau1elec2_Zmass_MET60_elec2tauSS->Fill(transverseMass(elecs[kk],met)+transverseMass(taus[ii],met), pu_rw);
		  Mt_elec1elec2_Zmass_MET60_elec2tauSS->Fill(transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
		  Mt_tau1elec1elec2_Zmass_MET60_elec2tauSS->Fill(transverseMass(taus[ii],met)+transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met), pu_rw);
		}


		Ht_Zmass_MET60->Fill(ht,pu_rw);
		Meff_Zmass_MET60->Fill(meff,pu_rw);
		MInvElec2Tau_vs_HT_Zmass_MET60->Fill(Elec2Tau.M(),ht,pu_rw);
		MInvElecTau_OS_Zmass_MET60->Fill(ElecTau_OS.M(),pu_rw);
		MInvElecTau_SS_Zmass_MET60->Fill(ElecTau_SS.M(),pu_rw);
		MInvElecElec_Zmass_MET60->Fill(ElecElec.M(),pu_rw);
		MInvElec1Tau_Zmass_MET60->Fill(Elec1Tau.M(),pu_rw);
		MInvElec2Tau_Zmass_MET60->Fill(Elec2Tau.M(),pu_rw);
		if (elec1tauOS) MInvElec1Tau_OS_Zmass_MET60->Fill(Elec1Tau_OS.M(),pu_rw);
		if (elec1tauSS) MInvElec1Tau_SS_Zmass_MET60->Fill(Elec1Tau_SS.M(),pu_rw);
		if (elec2tauOS) MInvElec2Tau_OS_Zmass_MET60->Fill(Elec2Tau_OS.M(),pu_rw);
		if (elec2tauSS) MInvElec2Tau_SS_Zmass_MET60->Fill(Elec2Tau_SS.M(),pu_rw);
	      }

	    }

	  }
	
	  //-----------------------------------------------------------//
      
	  eventPass = true;

	  //-------------------- Print Event Detail? ------------------//
	  if(do_detail==1){
	    //Print info for all objects in the event
	    printEvent();

	    //WRITE YOUR OWN 'printCandidate' FUNCTION IF YOU WANT TO DO THIS
	    //printCandidate(ii);
	  }
	  //-----------------------------------------------------------//

	  //CHANGE TO BE COMPATIBLE WITH FILLHISTOS FUNCTION IN INHERITED ANALYZER
	  if(do_plots>1) fillHistos();
	}
      }
    }  

    //Didn't make it to cuts because of prelim requirements
    if(!madeToCuts) totAnalyzed--;

    //----- Find the last cut the event passed, if it failed ------//
    if(!eventPass&&madeToCuts==1) failedCuts[lastPassedCut+1]++;
    //-------------------------------------------------------------//
  }

  //--------- Make efficiency table?
  if(do_eff) printEff(theCutNames.size());

  //--------- Make plots?
  if(do_plots>0){
    TFile of(out_file,"Recreate");


    EventN->Write();

    MLP_MVAout->Write();
    KNN_MVAout->Write();

    Minv->Write();
    dR_elecelec->Write();
    Tau1Eta->Write();
    Elec1Eta->Write();
    Elec2Eta->Write();
    Tau1Pt->Write();
    Elec1Pt->Write();
    Elec2Pt->Write();
    MaxPt->Write();
    Ht->Write();
    Meff->Write();
    MVAMEt->Write();
    Mt_elec1->Write();
    Mt_elec2->Write();
    Mt_tau1->Write();
    dPhi_tau1->Write();
    dPhi_elec1->Write();
    dPhi_elec2->Write();
    MInvElecElec_OS->Write();
    MInvElecElec_SS->Write();
    MInvElecTau_OS->Write();
    MInvElecTau_SS->Write();
    MInvElec1Tau_OS->Write();
    MInvElec1Tau_SS->Write();
    MInvElec2Tau_OS->Write();
    MInvElec2Tau_SS->Write();
    MInvElecElec->Write();
    MInvElec1Tau->Write();
    MInvElec2Tau->Write();
    MInvTriplet->Write();
    MInvElecElec_vs_MInvElec1Tau->Write();
    MInvElecElec_vs_MInvElec2Tau->Write();
    MInvElecElec_vs_MInvElecTau_OS->Write();
    MInvElecElec_vs_MInvElecTau_SS->Write();
    MInvElecElec_vs_MInvElec1Tau_OS->Write();
    MInvTriplet_vs_MInvElec1Tau_OS->Write();
    MInvElec1Tau_OS_vs_dPhi_tau->Write();
    MInvElec1Tau_OS_vs_dPhi_elec1->Write();
    MInvElec1Tau_OS_vs_dPhi_elec2->Write();
    MInvElec1Tau_OS_vs_MET->Write();
    MInvElec1Tau_OS_vs_HT->Write();
    MInvElec1Tau_OS_vs_mT_Elec1->Write();
    MInvElec1Tau_OS_vs_mT_Elec2->Write();
    MInvElec1Tau_OS_vs_mT_Tau->Write();
    MInvElecElec_vs_MInvElec1Tau_SS->Write();
    MInvTriplet_vs_MInvElec1Tau_SS->Write();
    MInvElec1Tau_SS_vs_dPhi_tau->Write();
    MInvElec1Tau_SS_vs_dPhi_elec1->Write();
    MInvElec1Tau_SS_vs_dPhi_elec2->Write();
    MInvElec1Tau_SS_vs_MET->Write();
    MInvElec1Tau_SS_vs_HT->Write();
    MInvElec1Tau_SS_vs_mT_Elec1->Write();
    MInvElec1Tau_SS_vs_mT_Elec2->Write();
    MInvElec1Tau_SS_vs_mT_Tau->Write();
    MInvElecElec_vs_MInvElec2Tau_OS->Write();
    MInvTriplet_vs_MInvElec2Tau_OS->Write();
    MInvElec2Tau_OS_vs_dPhi_tau->Write();
    MInvElec2Tau_OS_vs_dPhi_elec1->Write();
    MInvElec2Tau_OS_vs_dPhi_elec2->Write();
    MInvElec2Tau_OS_vs_MET->Write();
    MInvElec2Tau_OS_vs_HT->Write();
    MInvElec2Tau_OS_vs_mT_Elec1->Write();
    MInvElec2Tau_OS_vs_mT_Elec2->Write();
    MInvElec2Tau_OS_vs_mT_Tau->Write();
    MInvElecElec_vs_MInvElec2Tau_SS->Write();
    MInvTriplet_vs_MInvElec2Tau_SS->Write();
    MInvElec2Tau_SS_vs_dPhi_tau->Write();
    MInvElec2Tau_SS_vs_dPhi_elec1->Write();
    MInvElec2Tau_SS_vs_dPhi_elec2->Write();
    MInvElec2Tau_SS_vs_MET->Write();
    MInvElec2Tau_SS_vs_HT->Write();
    MInvElec2Tau_SS_vs_mT_Elec1->Write();
    MInvElec2Tau_SS_vs_mT_Elec2->Write();
    MInvElec2Tau_SS_vs_mT_Tau->Write();
    MInvElecElec_vs_MInvElec1Tau->Write();
    MInvTriplet_vs_MInvElec1Tau->Write();
    MInvElec1Tau_vs_dPhi_tau->Write();
    MInvElec1Tau_vs_dPhi_elec1->Write();
    MInvElec1Tau_vs_dPhi_elec2->Write();
    MInvElec1Tau_vs_MET->Write();
    MInvElec1Tau_vs_HT->Write();
    MInvElec1Tau_vs_mT_Elec1->Write();
    MInvElec1Tau_vs_mT_Elec2->Write();
    MInvElec1Tau_vs_mT_Tau->Write();
    MInvElecElec_vs_MInvElec2Tau->Write();
    MInvTriplet_vs_MInvElec2Tau->Write();
    MInvElec2Tau_vs_dPhi_tau->Write();
    MInvElec2Tau_vs_dPhi_elec1->Write();
    MInvElec2Tau_vs_dPhi_elec2->Write();
    MInvElec2Tau_vs_MET->Write();
    MInvElec2Tau_vs_HT->Write();
    MInvElec2Tau_vs_mT_Elec1->Write();
    MInvElec2Tau_vs_mT_Elec2->Write();
    MInvElec2Tau_vs_mT_Tau->Write();
    MInvElecElec_vs_dPhi_tau->Write();
    MInvElecElec_vs_dPhi_elec1->Write();
    MInvElecElec_vs_dPhi_elec2->Write();
    MInvElecElec_vs_MET->Write();
    MInvElecElec_vs_HT->Write();
    MInvElecElec_vs_mT_Elec1->Write();
    MInvElecElec_vs_mT_Elec2->Write();
    MInvElecElec_vs_mT_Tau->Write();
    MInvTriplet_vs_MInvElecElec->Write();
    MInvTriplet_vs_dPhi_tau->Write();
    MInvTriplet_vs_dPhi_elec1->Write();
    MInvTriplet_vs_dPhi_elec2->Write();
    MInvTriplet_vs_MET->Write();
    MInvTriplet_vs_HT->Write();
    MInvTriplet_vs_mT_Elec1->Write();
    MInvTriplet_vs_mT_Elec2->Write();
    MInvTriplet_vs_mT_Tau->Write();
    Mt_tau1elec1->Write();
    Mt_tau1elec2->Write();
    Mt_elec1elec2->Write();
    Mt_tau1elec1elec2->Write();
    Ht_MET60->Write();
    Meff_MET60->Write();
    MInvElec2Tau_vs_HT_MET60->Write();
    MInvElecTau_OS_MET60->Write();
    MInvElecTau_SS_MET60->Write();
    MInvElecElec_MET60->Write();
    MInvElec1Tau_MET60->Write();
    MInvElec2Tau_MET60->Write();
    MInvElec1Tau_OS_MET60->Write();
    MInvElec1Tau_SS_MET60->Write();
    MInvElec2Tau_OS_MET60->Write();
    MInvElec2Tau_SS_MET60->Write();
    Ht_Zmass->Write();
    Meff_Zmass->Write();
    MInvElec2Tau_vs_HT_Zmass->Write();
    MInvElecTau_OS_Zmass->Write();
    MInvElecTau_SS_Zmass->Write();
    MInvElecElec_Zmass->Write();
    MInvElec1Tau_Zmass->Write();
    MInvElec2Tau_Zmass->Write();
    MInvElec1Tau_OS_Zmass->Write();
    MInvElec1Tau_SS_Zmass->Write();
    MInvElec2Tau_OS_Zmass->Write();
    MInvElec2Tau_SS_Zmass->Write();
    Ht_Zmass_MET60->Write();
    Meff_Zmass_MET60->Write();
    MInvElec2Tau_vs_HT_Zmass_MET60->Write();
    MInvElecTau_OS_Zmass_MET60->Write();
    MInvElecTau_SS_Zmass_MET60->Write();
    MInvElecElec_Zmass_MET60->Write();
    MInvElec1Tau_Zmass_MET60->Write();
    MInvElec2Tau_Zmass_MET60->Write();
    MInvElec1Tau_OS_Zmass_MET60->Write();
    MInvElec1Tau_SS_Zmass_MET60->Write();
    MInvElec2Tau_OS_Zmass_MET60->Write();
    MInvElec2Tau_SS_Zmass_MET60->Write();

    Mt_tau1elec1_elec1tauOS->Write();
    Mt_tau1elec2_elec1tauOS->Write();
    Mt_elec1elec2_elec1tauOS->Write();
    Mt_tau1elec1elec2_elec1tauOS->Write();
    Mt_tau1elec1_elec1tauSS->Write();
    Mt_tau1elec2_elec1tauSS->Write();
    Mt_elec1elec2_elec1tauSS->Write();
    Mt_tau1elec1elec2_elec1tauSS->Write();
    Mt_tau1elec1_elec2tauOS->Write();
    Mt_tau1elec2_elec2tauOS->Write();
    Mt_elec1elec2_elec2tauOS->Write();
    Mt_tau1elec1elec2_elec2tauOS->Write();
    Mt_tau1elec1_elec2tauSS->Write();
    Mt_tau1elec2_elec2tauSS->Write();
    Mt_elec1elec2_elec2tauSS->Write();
    Mt_tau1elec1elec2_elec2tauSS->Write();

    Mt_tau1elec1_MET60->Write();
    Mt_tau1elec2_MET60->Write();
    Mt_elec1elec2_MET60->Write();
    Mt_tau1elec1elec2_MET60->Write();
    Mt_tau1elec1_MET60_elec1tauOS->Write();
    Mt_tau1elec2_MET60_elec1tauOS->Write();
    Mt_elec1elec2_MET60_elec1tauOS->Write();
    Mt_tau1elec1elec2_MET60_elec1tauOS->Write();
    Mt_tau1elec1_MET60_elec1tauSS->Write();
    Mt_tau1elec2_MET60_elec1tauSS->Write();
    Mt_elec1elec2_MET60_elec1tauSS->Write();
    Mt_tau1elec1elec2_MET60_elec1tauSS->Write();
    Mt_tau1elec1_MET60_elec2tauOS->Write();
    Mt_tau1elec2_MET60_elec2tauOS->Write();
    Mt_elec1elec2_MET60_elec2tauOS->Write();
    Mt_tau1elec1elec2_MET60_elec2tauOS->Write();
    Mt_tau1elec1_MET60_elec2tauSS->Write();
    Mt_tau1elec2_MET60_elec2tauSS->Write();
    Mt_elec1elec2_MET60_elec2tauSS->Write();
    Mt_tau1elec1elec2_MET60_elec2tauSS->Write();

    Mt_tau1elec1_Zmass->Write();
    Mt_tau1elec2_Zmass->Write();
    Mt_elec1elec2_Zmass->Write();
    Mt_tau1elec1elec2_Zmass->Write();
    Mt_tau1elec1_Zmass_elec1tauOS->Write();
    Mt_tau1elec2_Zmass_elec1tauOS->Write();
    Mt_elec1elec2_Zmass_elec1tauOS->Write();
    Mt_tau1elec1elec2_Zmass_elec1tauOS->Write();
    Mt_tau1elec1_Zmass_elec1tauSS->Write();
    Mt_tau1elec2_Zmass_elec1tauSS->Write();
    Mt_elec1elec2_Zmass_elec1tauSS->Write();
    Mt_tau1elec1elec2_Zmass_elec1tauSS->Write();
    Mt_tau1elec1_Zmass_elec2tauOS->Write();
    Mt_tau1elec2_Zmass_elec2tauOS->Write();
    Mt_elec1elec2_Zmass_elec2tauOS->Write();
    Mt_tau1elec1elec2_Zmass_elec2tauOS->Write();
    Mt_tau1elec1_Zmass_elec2tauSS->Write();
    Mt_tau1elec2_Zmass_elec2tauSS->Write();
    Mt_elec1elec2_Zmass_elec2tauSS->Write();
    Mt_tau1elec1elec2_Zmass_elec2tauSS->Write();

    Mt_tau1elec1_Zmass_MET60->Write();
    Mt_tau1elec2_Zmass_MET60->Write();
    Mt_elec1elec2_Zmass_MET60->Write();
    Mt_tau1elec1elec2_Zmass_MET60->Write();
    Mt_tau1elec1_Zmass_MET60_elec1tauOS->Write();
    Mt_tau1elec2_Zmass_MET60_elec1tauOS->Write();
    Mt_elec1elec2_Zmass_MET60_elec1tauOS->Write();
    Mt_tau1elec1elec2_Zmass_MET60_elec1tauOS->Write();
    Mt_tau1elec1_Zmass_MET60_elec1tauSS->Write();
    Mt_tau1elec2_Zmass_MET60_elec1tauSS->Write();
    Mt_elec1elec2_Zmass_MET60_elec1tauSS->Write();
    Mt_tau1elec1elec2_Zmass_MET60_elec1tauSS->Write();
    Mt_tau1elec1_Zmass_MET60_elec2tauOS->Write();
    Mt_tau1elec2_Zmass_MET60_elec2tauOS->Write();
    Mt_elec1elec2_Zmass_MET60_elec2tauOS->Write();
    Mt_tau1elec1elec2_Zmass_MET60_elec2tauOS->Write();
    Mt_tau1elec1_Zmass_MET60_elec2tauSS->Write();
    Mt_tau1elec2_Zmass_MET60_elec2tauSS->Write();
    Mt_elec1elec2_Zmass_MET60_elec2tauSS->Write();
    Mt_tau1elec1elec2_Zmass_MET60_elec2tauSS->Write();
    Ht_vs_Mt_tau1elec1elec2->Write();
    Meff_vs_Mt_tau1elec1elec2->Write();
    MVAMEt_vs_Mt_tau1elec1elec2->Write();
    MInvElecElec_vs_Mt_tau1elec1elec2->Write();
    MInvElec1Tau_vs_Mt_tau1elec1elec2->Write();
    MInvElec2Tau_vs_Mt_tau1elec1elec2->Write();
    MInvElec1Tau_OS_vs_Mt_tau1elec1elec2->Write();
    MInvElec2Tau_OS_vs_Mt_tau1elec1elec2->Write();
    MInvElec1Tau_SS_vs_Mt_tau1elec1elec2->Write();
    MInvElec2Tau_SS_vs_Mt_tau1elec1elec2->Write();
    MInvTriplet_vs_Mt_tau1elec1elec2->Write();




    of.Close();
  }
  if(do_plots>1) writeHistos();

  int numPassedCuts = totAnalyzed;
  for(int i=0;i<50;i++) numPassedCuts-=failedCuts[i];
  
  if(verbose>0) cout<<endl<<"Total Rate = "<<Minv->Integral()*scale<<endl;
  return make_pair(numPassedCuts,Minv->Integral()*scale);
}
