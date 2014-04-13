#include "MakeMVATree_eet.hh"

using namespace std;

ClassImp(MakeMVATree_eet)

//--------------------------------- Make Cuts
//If the candidate passes, returns (1,100)
//If it doesn't, returns (0,#FailedCut)
pair<bool,int> MakeMVATree_eet::makeCuts(int tauNum, int e1Num, int e2Num){
  pair<bool,int> cutResult;	

  //---------- Require Trigger -------------//
  // if((*HMT).eTauTauTriggerBit == 0 && theCuts[0][0] == 1) {cutResult = make_pair(0,0); return cutResult;}

  //Which trigger to use? For now leave single e trigger

  //---------- Require Trigger -------------//
  // if((*HMT).eTriggerBit == 0 && theCuts[0][0] == 1) {cutResult = make_pair(0,0); return cutResult;}

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


	cutResult = make_pair(1,100);
	return cutResult;
}

void MakeMVATree_eet::printCandidate(int tauNum, int e1Num, int e2Num){
//   TLorentzVector theMET;
//   double metpx = 0;//-elec.Px()-tau1.Px()-tau2.Px();
//   double metpy = 0;//-elec.Py()-tau1.Py()-tau2.Py();

//   TLorentzVector theJET;
//   for(unsigned int jj=0; jj<(*(*HMT).jetPt).size(); jj++){
//     //if(dR((*(*HMT).jetEta)[jj],(*(*HMT).jetPhi)[jj],elec.Eta(),elec.Phi())<0.2) continue;
//     //if(dR((*(*HMT).jetEta)[jj],(*(*HMT).jetPhi)[jj],tau1.Eta(),tau1.Phi())<0.2) continue;
//     //if(dR((*(*HMT).jetEta)[jj],(*(*HMT).jetPhi)[jj],tau2.Eta(),tau2.Phi())<0.2) continue;
    
//     theJET.SetPtEtaPhiE((*(*HMT).jetPt)[jj],(*(*HMT).jetEta)[jj],(*(*HMT).jetPhi)[jj],(*(*HMT).jetE)[jj]);
//     metpx = metpx - theJET.Px();
//     metpy = metpy - theJET.Py();
//   }

//   theMET.SetPxPyPzE(metpx,metpy,0,sqrt(pow(metpx,2)+pow(metpy,2)));

//   cout<<endl<<"Reco Level Stuffs"<<endl;
//   cout<<"------------------------------------------------------------------------------------//"<<endl;
//   cout<<"------------------------------------------------------------------------------------//"<<endl;
//   cout<<"                                   Candidate "<<endl;
//   cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
//   cout<<"Reco Electron"<<endl;
//   cout<<"\t\tPt = "<<elecs[tauNum].Pt()<<" Phi = "<<elecs[tauNum].Phi()<<" Eta = "<<elecs[tauNum].Eta()<<endl;
//   cout<<"\t\tPx = "<<elecs[tauNum].Px()<<" Py = "<<elecs[tauNum].Py()<<" Pz = "<<elecs[tauNum].Pz()<<endl;
//   cout<<"Reco Lead Tau"<<endl;
//   cout<<"\t\tPt = "<<taus[e1Num].Pt()<<" Phi = "<<taus[e1Num].Phi()<<" Eta = "<<taus[e1Num].Eta()<<endl;
//   cout<<"\t\tPx = "<<taus[e1Num].Px()<<" Py = "<<taus[e1Num].Py()<<" Pz = "<<taus[e1Num].Pz()<<endl;
//   cout<<"Reco Sub-Lead Tau"<<endl;
//   cout<<"\t\tPt = "<<taus[e2Num].Pt()<<" Phi = "<<taus[e2Num].Phi()<<" Eta = "<<taus[e2Num].Eta()<<endl;
//   cout<<"\t\tPx = "<<taus[e2Num].Px()<<" Py = "<<taus[e2Num].Py()<<" Pz = "<<taus[e2Num].Pz()<<endl;
//   cout<<"Reco Jets"<<endl;
//   for(unsigned int jj=0;jj<(*(*HMT).jetPt).size();jj++){
//     cout<<"Jet "<<jj<<"... E = "<<(*(*HMT).jetE)[jj]<<", Pt = "<<(*(*HMT).jetPt)[jj]<<", Eta = "<<(*(*HMT).jetEta)[jj]<<", Phi = "<<(*(*HMT).jetPhi)[jj]<<endl;
//   }
//   cout<<"MET: "<<endl;
//   cout<<"\tMEt Uncorr = "<<(*HMT).MEt<<"\tPhi = "<<(*HMT).MEtPhi<<endl;
//   cout<<"\tMEt Type01 = "<<(*HMT).MEtType01Corrected<<"\tPhi = "<<(*HMT).MEtType01CorrectedPhi<<endl;
//   cout<<"\tMEt MVA    = "<<(*HMT).MEtMVA<<"\tPhi = "<<(*HMT).MEtMVAPhi<<endl;
//   cout<<"\tMEt Candidates = "<<theMET.Pt()<<"\tPhi = "<<theMET.Phi()<<endl;
}


void MakeMVATree_eet::fillHistos(){
}

void MakeMVATree_eet::writeHistos(){
}

void MakeMVATree_eet::makeNewTree(TChain & theTree, char* outFile, char* outTreeName, char* cutFile, int verbosity){

  TH1F dummyHist("PU","PU",400,0,400);
  setupAnalyzer(theTree, outFile, 1.0, 1, cutFile, 0, 0, 0, 0, dummyHist, verbosity);



  //TTree outTree(outTreeName,outTreeName);
  //setup_branches_output(outTree,*HMT);



  Float_t Elec2Pt;
  Float_t Elec1Pt;
  Float_t TauPt;
  Float_t MET;
  Float_t Mt_Elec1Elec2;
  Float_t Mt_Elec2Tau;
  Float_t Mt_Elec1Tau;
  Float_t MaxPt;
  Float_t MInv_Elec1Elec2;
  Float_t MInv_Elec2Tau;
  Float_t MInv_Elec1Tau;
  Float_t MInv_Triplet;

  Float_t DRElec1Elec2;
  Float_t DRElec1Tau;
  Float_t DRElec2Tau;

  Float_t dPhi_elec1;
  Float_t dPhi_tau;
  Float_t dPhi_elec2;

  Float_t DiElec_eta;
  Float_t DiElec_PtRatio;


  // Float_t DRMuElec1;
  // Float_t DRMuElec2;
  // Float_t DRElec1Elec2;
  // Float_t PtRatio;

  TTree mvaTree("mva","mva");

  mvaTree.Branch("DRElec1Elec2",&DRElec1Elec2,"DRElec1Elec2/F");
  mvaTree.Branch("DRElec1Tau",&DRElec1Tau,"DRElec1Tau/F");
  mvaTree.Branch("DRElec2Tau",&DRElec2Tau,"DRElec2Tau/F");

  mvaTree.Branch("dPhi_elec1",&dPhi_elec1,"dPhi_elec1/F");
  mvaTree.Branch("dPhi_tau",&dPhi_tau,"dPhi_tau/F");
  mvaTree.Branch("dPhi_elec2",&dPhi_elec2,"dPhi_elec2/F");

  mvaTree.Branch("DiElec_eta",&DiElec_eta,"DiElec_eta/F");
  mvaTree.Branch("DiElec_PtRatio",&DiElec_PtRatio,"DiElec_PtRatio/F");


  mvaTree.Branch("Elec2Pt",&Elec2Pt,"Elec2Pt/F");
  mvaTree.Branch("Elec1Pt",&Elec1Pt,"Elec1Pt/F");
  mvaTree.Branch("TauPt",&TauPt,"TauPt/F");
  // mvaTree.Branch("Elec2Eta",&Elec2Eta,"Elec2Eta/F");
  // mvaTree.Branch("ElecEta",&ElecEta,"ElecEta/F");
  // mvaTree.Branch("TauEta",&TauEta,"TauEta/F");
  mvaTree.Branch("MET",&MET,"MET/F");
  mvaTree.Branch("Mt_Elec1Elec2",&Mt_Elec1Elec2,"Mt_Elec1Elec2/F");
  mvaTree.Branch("Mt_Elec2Tau",&Mt_Elec2Tau,"Mt_Elec2Tau/F");
  mvaTree.Branch("Mt_Elec1Tau",&Mt_Elec1Tau,"Mt_Elec1Tau/F");
  mvaTree.Branch("MaxPt",&MaxPt,"MaxPt/F");
  mvaTree.Branch("MInv_Elec1Elec2",&MInv_Elec1Elec2,"MInv_Elec1Elec2/F");
  mvaTree.Branch("MInv_Elec2Tau",&MInv_Elec2Tau,"MInv_Elec2Tau/F");
  mvaTree.Branch("MInv_Elec1Tau",&MInv_Elec1Tau,"MInv_Elec1Tau/F");
  mvaTree.Branch("MInv_Triplet",&MInv_Triplet,"MInv_Triplet/F");


  // mvaTree.Branch("DRMuDiElec",&DRMuDiElec,"DRMuDiElec/F");
  // mvaTree.Branch("DRMuElec1",&DRMuElec1,"DRMuElec1/F");
  // mvaTree.Branch("DRMuElec2",&DRMuElec2,"DRMuElec2/F");
  // mvaTree.Branch("DRElec1Elec2",&DRElec1Elec2,"DRElec1Elec2/F");
  // mvaTree.Branch("PtRatio",&PtRatio,"PtRatio/F");

  int cand_count = 0;

  //----------- Event Loop


  for(int i=0;i<Nentries;i++){

    if (i % 100000 == 0) std::cout << "i = " << i << std::endl;
    
    //Setup objects and parameters for each event
    setupEvent(theTree, i);
    
    //DO ANY CHECKING OF OBJECTS YOU ARE CONCERNED WITH HAVING HERE
    
    if (elecs.size()<2 || taus.size()<1) continue;
    //We're interested in analyzing this type of event...
    totAnalyzed++;

    //------------------------------------------ Candidate loop(s) ---------------------------------------//
    for(unsigned int ii=0; ii<taus.size(); ii++){                                              
      for(unsigned int jj=0; jj<elecs.size(); jj++){
	for(unsigned int kk=0; kk<elecs.size(); kk++){
	  
	  if (jj==kk) continue;

	  cutPair=makeCuts(ii,jj,kk);

	  //If passed, reset final passed cut to last cut
	  if(cutPair.first) cutPair.second=50;

	  //Last passing cut biggest so far?
	  if(cutPair.second-1>lastPassedCut) lastPassedCut = cutPair.second - 1;

	  //Didn't pass, move one
	  if(!cutPair.first) continue;	

	  //If you got here, the candidate passed
	  if(!eventPass){
	    //Write the tree
	    //if(verbose>0) cout<<"Filling Event "<<i<<"..."<<endl;
	    //outTree.Fill();
	    eventPass = true;
	    cand_count++;

	    MaxPt=elecs[jj].Pt();
	    if (elecs[kk].Pt()>MaxPt) MaxPt=elecs[kk].Pt();
	    if (taus[ii].Pt()>MaxPt) MaxPt=taus[ii].Pt();

	    Elec1Pt = elecs[jj].Pt();
	    Elec2Pt = elecs[kk].Pt();
	    TauPt = taus[ii].Pt();
	    // Elec2Eta = elecs[jj].Eta();
	    // ElecEta = elecs[kk].Eta();
	    // TauEta = taus[ii].Eta();
	    MET = (*HMT).MEtMVA;

	    Mt_Elec1Elec2 = transverseMass(elecs[jj],met)+transverseMass(elecs[kk],met);
	    Mt_Elec1Tau = transverseMass(taus[ii],met)+transverseMass(elecs[jj],met);
	    Mt_Elec2Tau = transverseMass(elecs[kk],met)+transverseMass(taus[ii],met);

	    TLorentzVector Elec2Elec;
	    Elec2Elec = elecs[jj]+elecs[kk];
	    TLorentzVector TauElec;
	    TauElec = taus[ii]+elecs[jj];
	    TLorentzVector Elec2Tau;
	    Elec2Tau = taus[ii]+elecs[kk];
	    TLorentzVector Triplet;
	    Triplet = taus[ii]+elecs[jj]+elecs[kk];


	    DiElec_eta = Elec2Elec.Eta();
	    DiElec_PtRatio = Elec2Elec.Pt()/(elecs[jj].Pt()+elecs[kk].Pt());

	    MInv_Elec1Elec2 = Elec2Elec.M();
	    MInv_Elec2Tau = Elec2Tau.M();
	    MInv_Elec1Tau = TauElec.M();
	    MInv_Triplet = Triplet.M();

	    dPhi_elec1 = dPhi(elecs[jj].Phi(),(*HMT).MEtMVAPhi);
	    dPhi_tau = dPhi(taus[ii].Phi(),(*HMT).MEtMVAPhi);
	    dPhi_elec2 = dPhi(elecs[kk].Phi(),(*HMT).MEtMVAPhi);
	    
	    DRElec1Elec2 = dR(elecs[jj].Eta(),elecs[jj].Phi(),(elecs[kk]).Eta(),(elecs[kk]).Phi());
	    DRElec1Tau = dR(taus[ii].Eta(),taus[jj].Phi(),(elecs[jj]).Eta(),(elecs[jj]).Phi());
	    DRElec2Tau = dR(elecs[kk].Eta(),elecs[kk].Phi(),(taus[ii]).Eta(),(taus[ii]).Phi());

	    // DRMuDiElec = dR(elecs[jj].Eta(),elecs[jj].Phi(),(elecs[kk]+elecs[kk]).Eta(),(elecs[kk]+elecs[kk]).Phi());
	    // DRMuElec1 = dR(elecs[jj].Eta(),elecs[jj].Phi(),(elecs[kk]).Eta(),(elecs[kk]).Phi());
	    // DRMuElec2 = dR(elecs[jj].Eta(),elecs[jj].Phi(),(elecs[kk]).Eta(),(elecs[kk]).Phi());
	    // DRElec1Elec2 = dR(elecs[kk].Eta(),elecs[kk].Phi(),(elecs[kk]).Eta(),(elecs[kk]).Phi());
	    // PtRatio = (elecs[kk]+elecs[kk]).Pt()/(elecs[kk].Pt()+elecs[kk].Pt());

	    mvaTree.Fill();
	    //break;
	  }	  
	}
      }
    }

    //Find the last cut the event passed, if it failed
    if(!eventPass) {
      failedCuts[lastPassedCut+1]++;
    }
  }

  //Make efficiency table?
  //theCuts.pop_back();
  //cout<<"CutNames.size() = "<<theCutNames.size()<<endl;
  //cout<<"Cuts.size() = "<<theCuts.size()<<endl;
  printEff(theCutNames.size());

  std::cout << outFile << std::endl;

  TFile outputFile(outFile,"RECREATE");
  //outTree.Write();
  mvaTree.Write();
  outputFile.Close();
}

pair<int,double> MakeMVATree_eet::analyze(TChain & theTree, double scaleFactor, char* outFile, int doCuts, char* cutFile, bool doEff, int doDetail, int doPlots, bool doPU, TH1F* puHisto, int verbosity){

  setupAnalyzer(theTree, outFile, scaleFactor, doCuts, cutFile, doEff, doDetail, doPlots, doPU, *puHisto, verbosity);

  bool madeToCuts=0;

  TH1F* ElecPt = new TH1F("ElecPt","p_{T}(#elec) (All elecs)",10000,0,200);
  TH1F* ElecEta = new TH1F("ElecEta","#eta(#elec) (All elecs)",10000,0,5);
  TH1F* ElecPhi = new TH1F("ElecPhi","#phi(#elec) (All elecs)",6400,0,3.2);
  TH1F* ElecE = new TH1F("ElecE","E(#elec) (All elecs)",10000,0,200);

  //----------- Event Loop
  for(int i=0;i<Nentries;i++){

    //Setup the objects and parameters for each event
    setupEvent(theTree, i);


    if(elecs.size()<2 || muons.size()<1) continue;

    //We're interested in analyzing this type of event...
    totAnalyzed++;

    madeToCuts=0;

    // for(unsigned int ii=0; ii<elecs.size(); ii++){
    //   if(elecs[ii].Pt()>15 && (*(*HMT).elecIdByVLooseCombinedIsolationDBSumPtCorr)[ii]>0 && (*(*HMT).elecIdByLooseElec2Rejection)[ii]>0 && (*(*HMT).elecIdByTightTautronRejection)[ii]>0){
    // 	ElecPt->Fill(elecs[ii].Pt());
    // 	ElecEta->Fill(fabs(elecs[ii].Eta()));
    // 	ElecPhi->Fill(elecs[ii].Phi());
    // 	ElecE->Fill(elecs[ii].E());
    //   }
    // }

    //------------------------------------------ Candidate loop(s) ---------------------------------------//
    /*for(unsigned int ii=0; ii<taus.size(); ii++){                                              
      for(unsigned int jj=0; jj<elecs.size(); jj++){
      for(unsigned int kk=0; kk<elecs.size(); kk++){
	  
      if(jj==kk) continue;         //Don't want elec1 = elec2
	  
      int elec12Opp = 0;
      if((*(*HMT).elecCharge)[jj]*(*(*HMT).tauCharge)[ii] < 0) elec12Opp = 1;
      if((*(*HMT).elecCharge)[kk]*(*(*HMT).tauCharge)[ii] < 0) elec12Opp = 2;
      //if(elec12Opp!=1&&elec12Opp!=2) continue;

      int elec12Same = 0;
      if((*(*HMT).elecCharge)[jj]*(*(*HMT).tauCharge)[ii] > 0) elec12Same = 1;
      if((*(*HMT).elecCharge)[kk]*(*(*HMT).tauCharge)[ii] > 0) elec12Same = 2;
      //if(elec12Same!=1&&elec12Same!=2) continue;

      madeToCuts = 1;

      //----------------------- Make Cuts? -------------------------//
      if(do_cuts!=0){	

      //CHANGE THIS TO BE COMPATIBLE WITH YOUR makeCuts FUNCTION
      cutPair=makeCuts(ii,jj,kk,elec12Same,elec12Opp);

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
      Minv->Fill(elecs[ii].M(),pu_rw); 
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
      }*/

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
    Minv->Write();

    ElecPt->Write();
    ElecEta->Write();
    ElecPhi->Write();
    ElecE->Write();

    of.Close();
  }
  if(do_plots>1) writeHistos();

  int numPassedCuts = totAnalyzed;
  for(int i=0;i<50;i++) numPassedCuts-=failedCuts[i];
  
  if(verbose>0) cout<<endl<<"Total Rate = "<<Minv->Integral()*scale<<endl;
  return make_pair(numPassedCuts,Minv->Integral()*scale);
}
