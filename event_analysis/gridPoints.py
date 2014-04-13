#This program gets the DG root files and classifies them by M1
import ROOT

histo_directory="/epp/scratch/atlas/ar273/Irvex/IrvexAnalysis/histos/output"

wA_slep_noWcascade_5 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144871.Herwigpp_simplifiedModel_wA_slep_noWcascade_5_ExampleAnalysis.root")
wA_slep_noWcascade_7 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144873.Herwigpp_simplifiedModel_wA_slep_noWcascade_7_ExampleAnalysis.root")
wA_slep_noWcascade_8 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144874.Herwigpp_simplifiedModel_wA_slep_noWcascade_8_ExampleAnalysis.root")
wA_slep_noWcascade_10 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144876.Herwigpp_simplifiedModel_wA_slep_noWcascade_10_ExampleAnalysis.root")
wA_slep_noWcascade_11 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144877.Herwigpp_simplifiedModel_wA_slep_noWcascade_11_ExampleAnalysis.root")
wA_slep_noWcascade_13 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144879.Herwigpp_simplifiedModel_wA_slep_noWcascade_13_ExampleAnalysis.root")
wA_slep_noWcascade_14 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144880.Herwigpp_simplifiedModel_wA_slep_noWcascade_14_ExampleAnalysis.root")
wA_slep_noWcascade_15 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144881.Herwigpp_simplifiedModel_wA_slep_noWcascade_15_ExampleAnalysis.root")
wA_slep_noWcascade_17 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144883.Herwigpp_simplifiedModel_wA_slep_noWcascade_17_ExampleAnalysis.root")
wA_slep_noWcascade_18 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144884.Herwigpp_simplifiedModel_wA_slep_noWcascade_18_ExampleAnalysis.root")
wA_slep_noWcascade_19 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144885.Herwigpp_simplifiedModel_wA_slep_noWcascade_19_ExampleAnalysis.root")
wA_slep_noWcascade_20 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144886.Herwigpp_simplifiedModel_wA_slep_noWcascade_20_ExampleAnalysis.root")
wA_slep_noWcascade_22 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144888.Herwigpp_simplifiedModel_wA_slep_noWcascade_22_ExampleAnalysis.root")
wA_slep_noWcascade_23 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144889.Herwigpp_simplifiedModel_wA_slep_noWcascade_23_ExampleAnalysis.root")
wA_slep_noWcascade_24 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144890.Herwigpp_simplifiedModel_wA_slep_noWcascade_24_ExampleAnalysis.root")
wA_slep_noWcascade_25 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144891.Herwigpp_simplifiedModel_wA_slep_noWcascade_25_ExampleAnalysis.root")
wA_slep_noWcascade_26 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144892.Herwigpp_simplifiedModel_wA_slep_noWcascade_26_ExampleAnalysis.root")
wA_slep_noWcascade_28 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144894.Herwigpp_simplifiedModel_wA_slep_noWcascade_28_ExampleAnalysis.root")
wA_slep_noWcascade_29 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144895.Herwigpp_simplifiedModel_wA_slep_noWcascade_29_ExampleAnalysis.root")
wA_slep_noWcascade_30 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.144896.Herwigpp_simplifiedModel_wA_slep_noWcascade_30_ExampleAnalysis.root")
wA_slep_noWcascade_32 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157461.Herwigpp_simplifiedModel_wA_slep_noWcascade_32_ExampleAnalysis.root")
wA_slep_noWcascade_35 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157464.Herwigpp_simplifiedModel_wA_slep_noWcascade_35_ExampleAnalysis.root")
wA_slep_noWcascade_38 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157467.Herwigpp_simplifiedModel_wA_slep_noWcascade_38_ExampleAnalysis.root")
wA_slep_noWcascade_39 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157954.Herwigpp_simplifiedModel_wA_slep_noWcascade_39_ExampleAnalysis.root")
wA_slep_noWcascade_40 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157955.Herwigpp_simplifiedModel_wA_slep_noWcascade_40_ExampleAnalysis.root")
wA_slep_noWcascade_41 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157956.Herwigpp_simplifiedModel_wA_slep_noWcascade_41_ExampleAnalysis.root")
wA_slep_noWcascade_42 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157957.Herwigpp_simplifiedModel_wA_slep_noWcascade_42_ExampleAnalysis.root")
wA_slep_noWcascade_43 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157958.Herwigpp_simplifiedModel_wA_slep_noWcascade_43_ExampleAnalysis.root")
wA_slep_noWcascade_44 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157959.Herwigpp_simplifiedModel_wA_slep_noWcascade_44_ExampleAnalysis.root")
wA_slep_noWcascade_45 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157960.Herwigpp_simplifiedModel_wA_slep_noWcascade_45_ExampleAnalysis.root")
wA_slep_noWcascade_46 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157961.Herwigpp_simplifiedModel_wA_slep_noWcascade_46_ExampleAnalysis.root")
wA_slep_noWcascade_47 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157962.Herwigpp_simplifiedModel_wA_slep_noWcascade_47_ExampleAnalysis.root")
wA_slep_noWcascade_48 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157963.Herwigpp_simplifiedModel_wA_slep_noWcascade_48_ExampleAnalysis.root")
wA_slep_noWcascade_49 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157964.Herwigpp_simplifiedModel_wA_slep_noWcascade_49_ExampleAnalysis.root")
wA_slep_noWcascade_50 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157965.Herwigpp_simplifiedModel_wA_slep_noWcascade_50_ExampleAnalysis.root")
wA_slep_noWcascade_51 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157966.Herwigpp_simplifiedModel_wA_slep_noWcascade_51_ExampleAnalysis.root")
wA_slep_noWcascade_52 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157967.Herwigpp_simplifiedModel_wA_slep_noWcascade_52_ExampleAnalysis.root")
wA_slep_noWcascade_53 =ROOT.TFile("output/2_9_Tight_n0046/mc12_8TeV.157968.Herwigpp_simplifiedModel_wA_slep_noWcascade_53_ExampleAnalysis.root")

gridA =   [
    wA_slep_noWcascade_5, 
    wA_slep_noWcascade_7, 
    wA_slep_noWcascade_8, 
    wA_slep_noWcascade_10, 
    wA_slep_noWcascade_11, 
    wA_slep_noWcascade_13, 
    wA_slep_noWcascade_14, 
    wA_slep_noWcascade_15, 
    wA_slep_noWcascade_17, 
    wA_slep_noWcascade_18, 
    wA_slep_noWcascade_19, 
    wA_slep_noWcascade_20, 
    wA_slep_noWcascade_22, 
    wA_slep_noWcascade_23, 
    wA_slep_noWcascade_24, 
    wA_slep_noWcascade_25, 
    wA_slep_noWcascade_26, 
    wA_slep_noWcascade_28, 
    wA_slep_noWcascade_29, 
    wA_slep_noWcascade_30, 
    wA_slep_noWcascade_32, 
    wA_slep_noWcascade_35, 
    wA_slep_noWcascade_38, 
    wA_slep_noWcascade_39, 
    wA_slep_noWcascade_40, 
    wA_slep_noWcascade_41, 
    wA_slep_noWcascade_42, 
    wA_slep_noWcascade_43, 
    wA_slep_noWcascade_44, 
    wA_slep_noWcascade_45, 
    wA_slep_noWcascade_46, 
    wA_slep_noWcascade_47, 
    wA_slep_noWcascade_48, 
    wA_slep_noWcascade_49, 
    wA_slep_noWcascade_50, 
    wA_slep_noWcascade_51, 
    wA_slep_noWcascade_52, 
    wA_slep_noWcascade_53
    ]



mass_pointsA = {
    wA_slep_noWcascade_5 : [112.5,   12.5 ],
    wA_slep_noWcascade_7 : [130.0, 30.0 ],
    wA_slep_noWcascade_8   :[155.0,    5.0  ],
    wA_slep_noWcascade_10  :[150.0,   50.0  ],
    wA_slep_noWcascade_11  :[175.0,   25.0  ],
    wA_slep_noWcascade_13 : [175.0, 75.0 ],
    wA_slep_noWcascade_14  :[200.0,   50.0  ],
    wA_slep_noWcascade_15  :[250.0,    0.0  ],
    wA_slep_noWcascade_17  :[225.0,  125.0  ],
    wA_slep_noWcascade_18  :[250.0,  100.0  ],
    wA_slep_noWcascade_19  :[300.0,   50.0  ],
    wA_slep_noWcascade_20  :[350.0,    0.0  ],
    wA_slep_noWcascade_22 : [300.0, 200.0],
    wA_slep_noWcascade_23  :[325.0,  175.0  ],
    wA_slep_noWcascade_24  :[375.0,  125.0  ],
    wA_slep_noWcascade_25  :[425.0,   75.0  ],
    wA_slep_noWcascade_26  :[500.0,    0.0  ],
    wA_slep_noWcascade_28 : [425.0, 325.0 ],
    wA_slep_noWcascade_29  :[450.0,  300.0  ],
    wA_slep_noWcascade_30  :[500.0,  250.0  ],
    wA_slep_noWcascade_32  :[550.0,  200.0  ],
    wA_slep_noWcascade_35  :[625.0,  125.0  ],
    wA_slep_noWcascade_38  :[750.0,    0.0  ],
    wA_slep_noWcascade_39  :[117.5,   82.5  ],
    wA_slep_noWcascade_40  :[142.5,  107.5  ],
    wA_slep_noWcascade_41  :[192.5,  157.5  ],
    wA_slep_noWcascade_42  :[267.5,  232.5  ],
    wA_slep_noWcascade_43  :[392.5,  357.5  ],
    wA_slep_noWcascade_44  :[517.5,  482.5  ],
    wA_slep_noWcascade_45  :[550.0,  450.0  ],
    wA_slep_noWcascade_46  :[575.0,  425.0  ],
    wA_slep_noWcascade_47  :[625.0,  375.0  ],
    wA_slep_noWcascade_48  :[675.0,  325.0  ],
    wA_slep_noWcascade_49  :[750.0,  250.0  ],
    wA_slep_noWcascade_50  :[642.5,  607.5  ],
    wA_slep_noWcascade_51  :[675.0,  575.0  ],
    wA_slep_noWcascade_52  :[700.0,  550.0  ],
    wA_slep_noWcascade_53  :[750.0,  500.0 ]
   }
