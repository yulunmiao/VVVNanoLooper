#include "Begin_3Lep2jet.h"

void Begin_3Lep2jet()
{
    //==============================================
    // Begin_3Lep2jet:
    // This function gets called prior to the event looping.
    // This is where one declares variables, histograms, event selections for the category 3Lep2jet.
    //==============================================

    // Create variables used in this category.
    // Please follow the convention of <category>_<varname> structure.
    ana.tx.createBranch<int>("3Lep2jet_intVar1");
    ana.tx.createBranch<float>("3Lep2jet_floatVar1");
    ana.tx.createBranch<LorentzVector>("3Lep2jet_LVVar1");

    // Define selections
    // CommonCut will contain selections that should be common to all categories, starting from this cut, add cuts for this category of the analysis.
    ana.cutflow.getCut("CommonCut");
    ana.cutflow.addCutToLastActiveCut("Cut_3Lep2jet_Preselection", [&]() { return ana.tx.getBranch<LorentzVector>("3Lep2jet_LVVar1").pt() > 25.;}, [&]() { return ana.tx.getBranch<float>("3Lep2jet_floatVar1"); } );

    // Create histograms used in this category.
    // Please follow the convention of h_<category>_<varname> structure.
    // N.B. Using nbins of size 180 or 360 can provide flexibility as it can be rebinned easily, as 180, 360 are highly composite numbers.
    RooUtil::Histograms hists_3Lep2jet;
    hists_3Lep2jet.addHistogram("h_3Lep2jet_intVar1", 10, 0, 10, [&]() { return ana.tx.getBranch<int>("3Lep2jet_intVar1"); } );
    hists_3Lep2jet.addHistogram("h_3Lep2jet_floatVar1", 180, 0, 500, [&]() { return ana.tx.getBranch<float>("3Lep2jet_floatVar1"); } );
    hists_3Lep2jet.addHistogram("h_3Lep2jet_LVVar1_Pt", 180, 0, 150, [&]() { return ana.tx.getBranch<LorentzVector>("3Lep2jet_LVVar1").pt(); } );

    // Now book cutflow histogram (could be commented out if user does not want.)
    // N.B. Cutflow histogramming can be CPU consuming.
    ana.cutflow.bookCutflows();

    // Book histograms to cuts that user wants for this category.
    ana.cutflow.bookHistogramsForCut(hists_3Lep2jet, "Cut_3Lep2jet_Preselection");
}
