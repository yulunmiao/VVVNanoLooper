#include "Begin_Common.h"

void Begin_Common()
{
    //==============================================
    // Begin_Common:
    // This function gets called prior to the event looping.
    // This is where one declares variables, histograms, event selections for the category Common.
    //==============================================

    // Create variables used in this category.
    // Please follow the convention of <category>_<varname> structure.

    // Event level information
    ana.tx.createBranch<int>                  ("Common_run");
    ana.tx.createBranch<int>                  ("Common_lumi");
    ana.tx.createBranch<unsigned long long>   ("Common_evt");
    ana.tx.createBranch<float>                ("Common_genWeight");
    ana.tx.createBranch<float>                ("Common_btagWeight_DeepCSVB");

    // 2016 only triggers
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"); // Lowest unprescaled
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL"); // Lowest unprescaled
    // The rest of the triggers
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8"); // Lowest unprescaled for >= 2017C
    ana.tx.createBranch<bool>                 ("Common_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
    ana.tx.createBranch<bool>                 ("Common_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"); // Lowest unprescaled
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"); // Lowest unprescaled
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"); // Lowest unprescaled
    ana.tx.createBranch<bool>                 ("Common_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL");
    // Summary triggers
    ana.tx.createBranch<bool>                 ("Common_HLT_DoubleEl");
    ana.tx.createBranch<bool>                 ("Common_HLT_MuEG");
    ana.tx.createBranch<bool>                 ("Common_HLT_DoubleMu");

    ana.tx.createBranch<bool>                 ("Common_pass_duplicate_removal_ee_em_mm"); // Flag to identify whether the event passes duplicate removal
    ana.tx.createBranch<bool>                 ("Common_pass_duplicate_removal_mm_em_ee"); // Flag to identify whether the event passes duplicate removal

    // Summary 4 vectors of the objects selected
    ana.tx.createBranch<LorentzVector>        ("Common_met_p4");
    ana.tx.createBranch<vector<LorentzVector>>("Common_lep_p4");      // Pt sorted selected lepton p4s (electrons and muons together)
    ana.tx.createBranch<vector<int>>          ("Common_lep_idxs");    // Pt sorted selected lepton idxs (electrons and muons together)
    ana.tx.createBranch<vector<int>>          ("Common_lep_pdgid");   // Pt sorted selected lepton pdgids (so that Common_lep_idxs can be used to access NanoAOD)
    ana.tx.createBranch<vector<int>>          ("Common_lep_tight");   // Pt sorted selected lepton tight (Where a tight version of the lepton isolation is used to reduce bkg a bit further if necessary)
    ana.tx.createBranch<vector<float>>        ("Common_lep_dxy");     // Pt sorted selected lepton dxy (electrons and muons together)
    ana.tx.createBranch<vector<float>>        ("Common_lep_dz");      // Pt sorted selected lepton dz (electrons and muons together)

    // Jet variables
    ana.tx.createBranch<vector<LorentzVector>>("Common_jet_p4");            // Pt sorted selected jet p4s
    ana.tx.createBranch<vector<int>>          ("Common_jet_idxs");          // Pt sorted selected jet idxs (To access rest of the jet variables in NanoAOD)
    ana.tx.createBranch<vector<bool>>         ("Common_jet_passBloose");    // Pt sorted selected jet idxs (To access rest of the jet variables in NanoAOD)
    ana.tx.createBranch<vector<bool>>         ("Common_jet_passBmedium");   // Pt sorted selected jet idxs (To access rest of the jet variables in NanoAOD)
    ana.tx.createBranch<vector<bool>>         ("Common_jet_passBtight");    // Pt sorted selected jet idxs (To access rest of the jet variables in NanoAOD)
    ana.tx.createBranch<vector<int>>          ("Common_jet_overlapfatjet"); // Pt sorted selected jet idxs (To access rest of the jet variables in NanoAOD)

    // Fat jet variables
    ana.tx.createBranch<vector<LorentzVector>>("Common_fatjet_p4");            // Pt sorted selected fatjet p4s
    ana.tx.createBranch<vector<int>>          ("Common_fatjet_idxs");          // Pt sorted selected fatjet idxs (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_msoftdrop");     // Pt sorted selected fatjet msoftdrop (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deepMD_W");      // Pt sorted selected fatjet FatJet_deepTagMD_WvsQCD (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deep_W");        // Pt sorted selected fatjet FatJet_deepTag_WvsQCD (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deepMD_Z");      // Pt sorted selected fatjet FatJet_deepTagMD_WvsQCD (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deep_Z");        // Pt sorted selected fatjet FatJet_deepTag_WvsQCD (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deepMD_T");      // Pt sorted selected fatjet FatJet_deepTagMD_TvsQCD (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deep_T");        // Pt sorted selected fatjet FatJet_deepTag_TvsQCD (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_deepMD_bb");     // Pt sorted selected fatjet FatJet_deepTagMD_bbvsLight (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_tau3");          // Pt sorted selected fatjet FatJet_deepTagMD_bbvsLight (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_tau2");          // Pt sorted selected fatjet FatJet_deepTagMD_bbvsLight (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_tau1");          // Pt sorted selected fatjet FatJet_deepTagMD_bbvsLight (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_tau32");         // Pt sorted selected fatjet FatJet_deepTagMD_bbvsLight (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_tau21");         // Pt sorted selected fatjet FatJet_deepTagMD_bbvsLight (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet0_pt");    // Pt sorted selected fatjet subjet p4 0 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet0_eta");   // Pt sorted selected fatjet subjet p4 0 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet0_phi");   // Pt sorted selected fatjet subjet p4 0 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet0_mass");  // Pt sorted selected fatjet subjet p4 0 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet1_pt");    // Pt sorted selected fatjet subjet p4 1 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet1_eta");   // Pt sorted selected fatjet subjet p4 2 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet1_phi");   // Pt sorted selected fatjet subjet p4 3 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<float>>        ("Common_fatjet_subjet1_mass");  // Pt sorted selected fatjet subjet p4 4 (To access rest of the fatjet variables in NanoAOD)
    ana.tx.createBranch<vector<LorentzVector>>("Common_fatjet_subjet0_p4");    // Pt sorted selected fatjet p4s
    ana.tx.createBranch<vector<LorentzVector>>("Common_fatjet_subjet1_p4");    // Pt sorted selected fatjet p4s

    // The n-loose b-tagged jets
    ana.tx.createBranch<int>                  ("Common_nb_loose");    // DeepFlav-B loose nb
    ana.tx.createBranch<int>                  ("Common_nb_medium");   // DeepFlav-B medium nb
    ana.tx.createBranch<int>                  ("Common_nb_tight");    // DeepFlav-B tight nb

    // The gen level information
    ana.tx.createBranch<vector<int>>          ("Common_gen_idx");        // Selected gen-particle idx in NanoAOD
    ana.tx.createBranch<vector<int>>          ("Common_gen_mother_idx"); // Selected gen-particle mother idx in NanoAOD
    ana.tx.createBranch<vector<int>>          ("Common_gen_mother_id");  // Selected gen-particle mother id in NanoAOD
    ana.tx.createBranch<vector<int>>          ("Common_gen_pdgid");      // Selected gen-particle pdgids
    ana.tx.createBranch<vector<LorentzVector>>("Common_gen_p4s");        // Selected gen-particle p4s

    ana.tx.createBranch<vector<int>>          ("Common_gen_vvvdecay_idx");          // Selected gen-particle of vvv decays idx in NanoAOD
    ana.tx.createBranch<vector<int>>          ("Common_gen_vvvdecay_mother_idx");   // Selected gen-particle of vvv decays mother idx in NanoAOD
    ana.tx.createBranch<vector<int>>          ("Common_gen_vvvdecay_mother_id");    // Selected gen-particle of vvv decays mother id in NanoAOD
    ana.tx.createBranch<vector<int>>          ("Common_gen_vvvdecay_pdgid");        // Selected gen-particle of vvv decays pdgids
    ana.tx.createBranch<vector<LorentzVector>>("Common_gen_vvvdecay_p4s");          // Selected gen-particle of vvv decays p4s
    ana.tx.createBranch<vector<int>>          ("Common_gen_vvvdecay_taudecayid");   // If gentau - flag the decay of the gentau

    ana.tx.createBranch<int>                  ("n_W");
    ana.tx.createBranch<int>                  ("n_Z");
    ana.tx.createBranch<int>                  ("n_lep_Z");
    ana.tx.createBranch<int>                  ("n_leptau_Z");
    ana.tx.createBranch<int>                  ("n_hadtau_Z");
    ana.tx.createBranch<int>                  ("n_nu_Z");
    ana.tx.createBranch<int>                  ("n_b_Z");
    ana.tx.createBranch<int>                  ("n_lep_W");
    ana.tx.createBranch<int>                  ("n_leptau_W");
    ana.tx.createBranch<int>                  ("n_hadtau_W");
    ana.tx.createBranch<bool>                 ("haslepWSS");  // includes leptonic tau decays

    ana.tx.createBranch<float>                ("Common_genHT");       // Gen HT value for stitching HT-sliced samples
    ana.tx.createBranch<int>                  ("Common_gen_n_light_lep"); // Gen value of how many light lepton exists

    // Define selections
    // CommonCut will contain selections that should be common to all categories, starting from this cut, add cuts for this category of the analysis.
    ana.cutflow.addCut("Wgt", [&]() { return 1; }, [&]() { if (not nt.isData()) return (nt.genWeight() > 0) - (nt.genWeight() < 0); else return 1; } );
    ana.cutflow.addCutToLastActiveCut("CommonCut", [&]() { return 1;}, [&]() { return 1; } );

    // Create histograms used in this category.
    // Please follow the convention of h_<category>_<varname> structure.
    // N.B. Using nbins of size 180 or 360 can provide flexibility as it can be rebinned easily, as 180, 360 are highly composite numbers.
    RooUtil::Histograms hists_Common;
    hists_Common.addHistogram("h_Common_nLep", 10, 0, 10, [&]() { return ana.tx.getBranchLazy<vector<int>>("Common_lep_idxs").size(); } );
    hists_Common.addHistogram("h_Common_nJet", 10, 0, 10, [&]() { return ana.tx.getBranchLazy<vector<int>>("Common_jet_idxs").size(); } );
    hists_Common.addHistogram("h_Common_nFatJet", 10, 0, 10, [&]() { return ana.tx.getBranchLazy<vector<int>>("Common_fatjet_idxs").size(); } );
    hists_Common.addHistogram("h_Common_nGenW", 100, 0, 100, [&]() { return (ana.tx.getBranchLazy<int>("n_W")>=0 ? (ana.tx.getBranchLazy<int>("n_W") +ana.tx.getBranchLazy<int>("n_lep_W")+ana.tx.getBranchLazy<int>("n_leptau_W")+ana.tx.getBranchLazy<int>("n_hadtau_W")+ (ana.tx.getBranchLazy<int>("n_lep_W")>0 ? 3:0) + (ana.tx.getBranchLazy<int>("n_leptau_W")>0 ? 9:0) + (ana.tx.getBranchLazy<int>("n_hadtau_W")>0 ? 21:0) +(ana.tx.getBranchLazy<bool>("haslepWSS") ? 46:0)) : -999); });
    hists_Common.addHistogram("h_Common_nGenZ", 300, 0, 300, [&]() { return (ana.tx.getBranchLazy<int>("n_Z")>=0 ? (ana.tx.getBranchLazy<int>("n_Z") +ana.tx.getBranchLazy<int>("n_lep_Z")+ana.tx.getBranchLazy<int>("n_leptau_Z")+ana.tx.getBranchLazy<int>("n_hadtau_Z")+ana.tx.getBranchLazy<int>("n_nu_Z")+ana.tx.getBranchLazy<int>("n_b_Z")+ (ana.tx.getBranchLazy<int>("n_lep_Z")>0 ? 3:0) + (ana.tx.getBranchLazy<int>("n_leptau_Z")>0 ? 12:0) + (ana.tx.getBranchLazy<int>("n_hadtau_Z")>0 ? 30:0) + (ana.tx.getBranchLazy<int>("n_nu_Z")>0 ? 67:0) + (ana.tx.getBranchLazy<int>("n_b_Z")>0 ? 140:0) ) : -999); });
    hists_Common.addHistogram("h_Common_isSS", 2, 0, 2, [&]() { return (ana.tx.getBranchLazy<int>("n_W")>=0 ? (ana.tx.getBranchLazy<bool>("haslepWSS") ? 1. : 0.) : -999.); } );

    // Book histograms to cuts that user wants for this category.
    ana.cutflow.bookHistogramsForCut(hists_Common, "CommonCut");

    // Book histograms to Root to count total number of events processed
    RooUtil::Histograms n_event_hist;
    n_event_hist.addHistogram("h_nevents", 1, 0, 1, [&]() { return 0; } );

    // Book the counter histogram to the Root
    ana.cutflow.bookHistogramsForCut(n_event_hist, "Root");
    ana.cutflow.bookHistogramsForCut(n_event_hist, "Wgt");
}
