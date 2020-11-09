#include "Process_SS2jet.h"

void Process_SS2jet(){
    //==============================================
    // Process_SS2jet:
    // This function gets called during the event looping.
    // This is where one sets the variables used for the category SS2jet.
    //==============================================

    // Set variables used in this category.
    // If histograms are booked with these variables the histograms will be filled automatically.
    // Please follow the convention of <category>_<varname> structure.
    //ana.tx.setBranch<int>("SS2jet_intVar1", -999);
    //ana.tx.setBranch<float>("SS2jet_floatVar1", -999);

    // Example of reading from Nano
    // std::vector<LorentzVector> electron_p4s = nt.Electron_p4(); // nt is a global variable that accesses NanoAOD
    // std::vector<float> electron_mvaTTH = nt.Electron_mvaTTH(); // electron ttH MVA scores from NanoAOD
    // Semi-complete list of NanoAOD for 102X can be found here: https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
    // Also consult here: https://github.com/cmstas/NanoTools/blob/d641a6d6c1aa9ecc8094a1af73d5e1bd7d6502ab/NanoCORE/Nano.h#L4875 (if new variables are added they may show up in master)

    //LorentzVector LV_SS2jet_LVVar1 = RooUtil::Calc::getLV(34.5, 1.2, 3.123, 0.105); // RooUtil::Calc::getLV() creates 4 vector
    //ana.tx.setBranch<LorentzVector>("SS2jet_LVVar1", LV_SS2jet_LVVar1);
    //raw geninfo
    
    if(!nt.isData()){
	for(unsigned int igen=0;igen<nt.GenPart_p4().size();igen++){
		ana.tx.pushbackToBranch<int>		("SS2jet_raw_gen_idx", igen);                                                            // Selected gen-particle idx in NanoAOD
		ana.tx.pushbackToBranch<int>		("SS2jet_raw_gen_mother_idx", nt.GenPart_genPartIdxMother()[igen]);                      // Selected gen-particle mother idx in NanoAOD
		ana.tx.pushbackToBranch<int>		("SS2jet_raw_gen_mother_id",  nt.GenPart_pdgId()[nt.GenPart_genPartIdxMother()[igen] ]); // Selected gen-particle mother idx in NanoAOD
		ana.tx.pushbackToBranch<int>		("SS2jet_raw_gen_pdgid", nt.GenPart_pdgId()[igen]);                                      // Selected gen-particle pdgids
		ana.tx.pushbackToBranch<LorentzVector>	("SS2jet_raw_gen_p4s", nt.GenPart_p4()[igen]);                                           // Selected gen-particle
		ana.tx.pushbackToBranch<int>	  	("SS2jet_raw_gen_status",nt.GenPart_status()[igen]);
		ana.tx.pushbackToBranch<int>		("SS2jet_raw_gen_statusFlags",nt.GenPart_statusFlags()[igen]);
	}
	for(unsigned int igenjet=0;igenjet<nt.GenJet_p4().size();igenjet++){
		ana.tx.pushbackToBranch<LorentzVector>  ("SS2jet_raw_genjet_p4",nt.GenJet_p4()[igenjet]);  
                ana.tx.pushbackToBranch<int>            ("SS2jet_raw_genjet_partonFlavour",nt.GenJet_partonFlavour()[igenjet]);
	}
    }
    
    //raw nanoinfo
    ana.tx.setBranch<int>       ("SS2jet_raw_nlep",nt.Muon_p4().size()+nt.Electron_p4().size());
    ana.tx.setBranch<int>	("SS2jet_raw_njet",nt.Jet_p4().size());
    ana.tx.setBranch<int>       ("SS2jet_raw_nfatjet",nt.FatJet_p4().size());

    ana.tx.setBranch<int>	("SS2jet_nIsoTrack",nt.nIsoTrack());
    //loop over all common leptons    
    //loop over all electrons
    for(unsigned int iel=0;iel<nt.Electron_p4().size();iel++){
        bool ele_tight;
	if(!(nt.Electron_mvaFall17V2Iso_WP90().at(iel))) continue;
        if(!(nt.Electron_p4().at(iel).pt()>10)) continue;
	if(!(fabs(nt.Electron_p4().at(iel).eta())<2.5)) continue;
	//if(fabs(nt.Electron_p4().at(iel).eta())<1.556&&fabs(nt.Electron_p4().at(iel).eta())>1.442) continue;
	if(!(nt.Electron_ip3d().at(iel)<0.01)) continue;
	if(!(fabs(nt.Electron_dxy().at(iel))<0.05)) continue;
	if(!(fabs(nt.Electron_dz().at(iel))<0.1)) continue;

	ele_tight=nt.Electron_p4().at(iel).pt()>25 && nt.Electron_mvaFall17V2Iso_WP80().at(iel) && !(fabs(nt.Electron_p4().at(iel).eta())<1.556 && fabs(nt.Electron_p4().at(iel).eta())>1.442);

	ana.tx.pushbackToBranch<int>("SS2jet_lep_idx", iel);
	ana.tx.pushbackToBranch<int>("SS2jet_lep_pdgid", nt.Electron_pdgId().at(iel));
	ana.tx.pushbackToBranch<LorentzVector>("SS2jet_lep_p4", nt.Electron_p4().at(iel));
        ana.tx.pushbackToBranch<bool>("SS2jet_lep_tight",ele_tight);
    }
    //loop over all muons
    for(unsigned int imu=0;imu<nt.Muon_p4().size();imu++){
	bool mu_tight;
	if(!(nt.Muon_mediumId().at(imu))) continue;
	if(!(nt.Muon_p4().at(imu).pt()>6)) continue;
	if(!(fabs(nt.Muon_p4().at(imu).eta())<2.4)) continue;
	if(!(nt.Muon_ip3d().at(imu)<0.015)) continue;
	if(!(nt.Muon_sip3d().at(imu)<4)) continue;
	if(!(fabs(nt.Muon_dxy().at(imu))<0.05)) continue;
	if(!(fabs(nt.Muon_dz().at(imu))<0.1)) continue;
	if(!(nt.Muon_pfRelIso03_all().at(imu)<0.4)) continue;
	
	mu_tight=nt.Muon_p4().at(imu).pt()>25 && nt.Muon_pfRelIso03_all().at(imu)<0.04;

	ana.tx.pushbackToBranch<int>("SS2jet_lep_idx", imu);
	ana.tx.pushbackToBranch<int>("SS2jet_lep_pdgid", nt.Muon_pdgId().at(imu));
        ana.tx.pushbackToBranch<LorentzVector>("SS2jet_lep_p4", nt.Muon_p4().at(imu));
        ana.tx.pushbackToBranch<bool>("SS2jet_lep_tight",mu_tight);
   }
   //b-tagging counter for SS1FatJet
   float bWPloose  = 0.0614;// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
   float bWPmedium = 0.3093;// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
   float bWPtight  = 0.7221;// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation2016Legacy
   if(nt.year() == 2017){
	bWPloose  = 0.0521;    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
	bWPmedium = 0.3033;    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
	bWPtight  = 0.7489;    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
   }
   if(nt.year() == 2018){
	bWPloose  = 0.0494;    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation102X
	bWPmedium = 0.2770;    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation102X
	bWPtight  = 0.7264;    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation102X
   }
   int SS2jet_nb_loose = 0;
   int SS2jet_nb_medium = 0;
   int SS2jet_nb_tight = 0;
   //loop over all jets
   for(unsigned int ijet=0;ijet<nt.Jet_p4().size();ijet++){
	if(!(nt.Jet_p4().at(ijet).pt()>20)) continue;
        if(!(fabs(nt.Jet_p4().at(ijet).eta())<2.4)) continue;
	bool overlap=false;
	//overlap removal of jet in dR=0.4 of lepton
	for(unsigned int ilep=0;ilep<ana.tx.getBranchLazy<vector<int>>("SS2jet_lep_idx").size();ilep++){
                int lepidx=     ana.tx.getBranchLazy<vector<int>>("SS2jet_lep_idx").at(ilep);
                int leppdgid=   ana.tx.getBranchLazy<vector<int>>("SS2jet_lep_pdgid").at(ilep);
		bool leptight=	ana.tx.getBranchLazy<vector<bool>>("SS2jet_lep_tight").at(ilep);
		if(!leptight) continue;
                LorentzVector lepp4=    fabs(leppdgid)==11?nt.Electron_p4().at(lepidx):nt.Muon_p4().at(lepidx);

                if(RooUtil::Calc::DeltaR(nt.Jet_p4().at(ijet),lepp4)<0.4){
                        overlap=true;break;
                }
        }
//	if(overlap==true) continue;
        ana.tx.pushbackToBranch<int>("SS2jet_jet_idx", ijet);
        ana.tx.pushbackToBranch<LorentzVector>("SS2jet_jet_p4", nt.Jet_p4()[ijet]);
        ana.tx.pushbackToBranch<bool>("SS2jet_jet_overlaplep",overlap);
        ana.tx.pushbackToBranch<bool>("SS2jet_jet_passBloose" , nt.Jet_btagDeepFlavB()[ijet] > bWPloose );
        ana.tx.pushbackToBranch<bool>("SS2jet_jet_passBmedium", nt.Jet_btagDeepFlavB()[ijet] > bWPmedium);
        ana.tx.pushbackToBranch<bool>("SS2jet_jet_passBtight" , nt.Jet_btagDeepFlavB()[ijet] > bWPtight );
	ana.tx.pushbackToBranch<int> ("SS2jet_jet_genJetIdx",nt.Jet_genJetIdx()[ijet]);
        if (nt.Jet_btagDeepFlavB()[ijet] > bWPloose)	SS2jet_nb_loose++;
        if (nt.Jet_btagDeepFlavB()[ijet] > bWPmedium)	SS2jet_nb_medium++;
        if (nt.Jet_btagDeepFlavB()[ijet] > bWPtight)	SS2jet_nb_tight++;
   }
   ana.tx.setBranch<int>("SS2jet_nb_loose", SS2jet_nb_loose);
   ana.tx.setBranch<int>("SS2jet_nb_medium", SS2jet_nb_medium);
   ana.tx.setBranch<int>("SS2jet_nb_tight", SS2jet_nb_tight);
   //loop over all fatjets
   for(unsigned int ifatjet=0;ifatjet<nt.FatJet_p4().size();ifatjet++){
	if(!(nt.FatJet_p4().at(ifatjet).pt()>180)) continue;
	if(!(fabs(nt.FatJet_p4().at(ifatjet).eta())<2.5)) continue;
	bool overlap=false;
	//overlap removal of fatjet in dR=0.8 of lepton
	for(unsigned int ilep=0;ilep<ana.tx.getBranchLazy<vector<int>>("SS2jet_lep_idx").size();ilep++){
		int lepidx=	ana.tx.getBranchLazy<vector<int>>("SS2jet_lep_idx").at(ilep);
		int leppdgid=	ana.tx.getBranchLazy<vector<int>>("SS2jet_lep_pdgid").at(ilep);
                bool leptight=  ana.tx.getBranchLazy<vector<bool>>("SS2jet_lep_tight").at(ilep);
                if(!leptight) continue;
		LorentzVector lepp4=	fabs(leppdgid)==11?nt.Electron_p4().at(lepidx):nt.Muon_p4().at(lepidx);

		if(RooUtil::Calc::DeltaR(nt.FatJet_p4().at(ifatjet),lepp4)<0.8){
			overlap=true;break;
		}
	}
	if(overlap==true) continue;
	
	ana.tx.pushbackToBranch<int>("SS2jet_fatjet_idx", ifatjet);
        ana.tx.pushbackToBranch<LorentzVector>("SS2jet_fatjet_p4", nt.FatJet_p4()[ifatjet]);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_msoftdrop", nt.FatJet_msoftdrop()[ifatjet]);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_deepMD_W", nt.FatJet_deepTagMD_WvsQCD()[ifatjet]);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_deep_W", nt.FatJet_deepTag_WvsQCD()[ifatjet]);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_deepMD_Z", nt.FatJet_deepTagMD_ZvsQCD()[ifatjet]);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_deep_Z", nt.FatJet_deepTag_ZvsQCD()[ifatjet]);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_deepMD_T", nt.FatJet_deepTagMD_TvsQCD()[ifatjet]);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_deep_T", nt.FatJet_deepTag_TvsQCD()[ifatjet]);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_deepMD_bb", nt.FatJet_deepTagMD_bbvsLight()[ifatjet]);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_tau3",  nt.FatJet_tau3()[ifatjet]);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_tau2",  nt.FatJet_tau2()[ifatjet]);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_tau1",  nt.FatJet_tau1()[ifatjet]);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_tau32", nt.FatJet_tau2()[ifatjet]!=0 ? nt.FatJet_tau3()[ifatjet] / nt.FatJet_tau2()[ifatjet] : -999.f);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_tau21", nt.FatJet_tau1()[ifatjet]!=0 ? nt.FatJet_tau2()[ifatjet] / nt.FatJet_tau1()[ifatjet] : -999.f);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_subjet0_pt",   nt.FatJet_subJetIdx1()[ifatjet] >= 0 ? nt.SubJet_pt()[  nt.FatJet_subJetIdx1()[ifatjet]] : -999.f);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_subjet0_eta",  nt.FatJet_subJetIdx1()[ifatjet] >= 0 ? nt.SubJet_eta()[ nt.FatJet_subJetIdx1()[ifatjet]] : -999.f);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_subjet0_phi",  nt.FatJet_subJetIdx1()[ifatjet] >= 0 ? nt.SubJet_phi()[ nt.FatJet_subJetIdx1()[ifatjet]] : -999.f);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_subjet0_mass", nt.FatJet_subJetIdx1()[ifatjet] >= 0 ? nt.SubJet_mass()[nt.FatJet_subJetIdx1()[ifatjet]] : -999.f);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_subjet1_pt",   nt.FatJet_subJetIdx2()[ifatjet] >= 0 ? nt.SubJet_pt()[  nt.FatJet_subJetIdx2()[ifatjet]] : -999.f);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_subjet1_eta",  nt.FatJet_subJetIdx2()[ifatjet] >= 0 ? nt.SubJet_eta()[ nt.FatJet_subJetIdx2()[ifatjet]] : -999.f);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_subjet1_phi",  nt.FatJet_subJetIdx2()[ifatjet] >= 0 ? nt.SubJet_phi()[ nt.FatJet_subJetIdx2()[ifatjet]] : -999.f);
        ana.tx.pushbackToBranch<float>("SS2jet_fatjet_subjet1_mass", nt.FatJet_subJetIdx2()[ifatjet] >= 0 ? nt.SubJet_mass()[nt.FatJet_subJetIdx2()[ifatjet]] : -999.f);
        ana.tx.pushbackToBranch<LorentzVector>("SS2jet_fatjet_subjet0_p4",  nt.FatJet_subJetIdx1()[ifatjet] >= 0 ? (RooUtil::Calc::getLV(nt.SubJet_pt()[nt.FatJet_subJetIdx1()[ifatjet]], nt.SubJet_eta()[nt.FatJet_subJetIdx1()[ifatjet]], nt.SubJet_phi()[nt.FatJet_subJetIdx1()[ifatjet]], nt.SubJet_mass()[nt.FatJet_subJetIdx1()[ifatjet]])) : (RooUtil::Calc::getLV(0., 0., 0., 0.)));
        ana.tx.pushbackToBranch<LorentzVector>("SS2jet_fatjet_subjet1_p4",  nt.FatJet_subJetIdx2()[ifatjet] >= 0 ? (RooUtil::Calc::getLV(nt.SubJet_pt()[nt.FatJet_subJetIdx2()[ifatjet]], nt.SubJet_eta()[nt.FatJet_subJetIdx2()[ifatjet]], nt.SubJet_phi()[nt.FatJet_subJetIdx2()[ifatjet]], nt.SubJet_mass()[nt.FatJet_subJetIdx2()[ifatjet]])) : (RooUtil::Calc::getLV(0., 0., 0., 0.)));
	}
   //sort the leptons by pt
   ana.tx.sortVecBranchesByPt(
   /* name of the 4vector branch to use to pt sort by*/               "SS2jet_lep_p4",
   /* names of any associated vector<float> branches to sort along */ {},
   /* names of any associated vector<int>   branches to sort along */ {"SS2jet_lep_idx", "SS2jet_lep_pdgid"},
   /* names of any associated vector<bool>  branches to sort along */ {"SS2jet_lep_tight"}
   );
   //sort the jets by pt
   ana.tx.sortVecBranchesByPt(
   /* name of the 4vector branch to use to pt sort by*/               "SS2jet_jet_p4",
   /* names of any associated vector<float> branches to sort along */ {},
   /* names of any associated vector<int>   branches to sort along */ {"SS2jet_jet_idx","SS2jet_jet_genJetIdx"},
   /* names of any associated vector<bool>  branches to sort along */ {"SS2jet_jet_passBloose","SS2jet_jet_passBmedium","SS2jet_jet_passBtight","SS2jet_jet_overlaplep"}
   );

   //not sorting the fatjet since requiring nfatjet==1
}

	

void PostProcess_SS2jet(){
    //if (ana.cutflow.getCut("SS2jet_bVeto").pass){
    if (ana.cutflow.getCut("SS2jet_FatJetCut").pass){
                   ana.tx.fill(); 
    }
}
  
