import ROOT
from math import sqrt,log
import cutlist
from optparse import OptionParser
def Z(S, B):
   return sqrt(2*((S+B)*log(1.0+S/B)-S))

def evnum(cut, file):
	file.cd(); hist = file.Get("Event_N_"+cut);
	#print file.GetName(), cut
	if not "Data" in file.GetName():
		return str(round(hist.GetBinContent(1), 1)) + " $\\pm$ " + str(round(hist.GetBinError(1), 1))
	else:
		return str(round(hist.GetBinContent(1), 1))
		

parser = OptionParser()
parser.add_option("-l", "--lumi", dest="lumi", type = "string",
                  help="Luminosity", default = "5000.0")
(options, args) = parser.parse_args()

#working points:
#lambda 40, tb 30
#lambda 50, tb 40
#lambda 50, tb 20

GMSB1_file = ROOT.TFile("mc11_7TeV.137940.GMSB_3_2d_40_250_3_30_1_1_herwigpp_" + options.lumi + "pb.root")
GMSB2_file = ROOT.TFile("mc11_7TeV.137950.GMSB_3_2d_50_250_3_40_1_1_herwigpp_" + options.lumi + "pb.root")
GMSB3_file = ROOT.TFile("mc11_7TeV.137948.GMSB_3_2d_50_250_3_20_1_1_herwigpp_" + options.lumi + "pb.root")
ttbar_file = ROOT.TFile("ttbar_McAtNLO.root")
Wjets_file = ROOT.TFile("AlpgenJimmyWjets.root")
Zjets_file = ROOT.TFile("AlpgenJimmyWjets.root")
QCD_file = ROOT.TFile("pythia_jetjet.root")
dibosons_file = ROOT.TFile("dibosons.root")
drellyan_file = ROOT.TFile("drellyan.root")
data_file = ROOT.TFile("Data.root")

data_periodB_file = ROOT.TFile("DataPeriodB.root")
data_periodD_file = ROOT.TFile("DataPeriodB.root")
data_periodE_file = ROOT.TFile("DataPeriodE.root")
data_periodF_file = ROOT.TFile("DataPeriodF.root")
data_periodG_file = ROOT.TFile("DataPeriodG.root")
data_periodH_file = ROOT.TFile("DataPeriodH.root")
data_periodI_file = ROOT.TFile("DataPeriodI.root")
data_periodJ_file = ROOT.TFile("DataPeriodJ.root")
data_periodK_file = ROOT.TFile("DataPeriodK.root")
data_periodL_file = ROOT.TFile("DataPeriodL.root")
data_periodM_file = ROOT.TFile("DataPeriodM.root")


SM_file = ROOT.TFile("standard_model.root")

files1 = [ QCD_file,    
           ttbar_file,
           Wjets_file,
           Zjets_file,
           drellyan_file,
           dibosons_file,
           data_file]

files2 = [SM_file,
          data_file,
          GMSB1_file,
          GMSB2_file,
          GMSB3_file,
          ]

files3 = [data_periodB_file,
          data_periodD_file,
          data_periodE_file,
          data_periodF_file,
          data_periodG_file,
          data_periodH_file,
          data_periodI_file,
          data_periodJ_file,
          data_periodK_file,
          data_periodL_file,
          data_periodM_file,
          ]


filenames1= {QCD_file  		:"Dijets",
             ttbar_file		:"$t\\bar{t}$",
             Wjets_file		:"W + jets",
             Zjets_file		:"Z + jets",
             dibosons_file	:"Dibosons",
             drellyan_file	:"Drell Yan",
             data_file          :"Data"} 

filenames2= {SM_file   		:"SM",
             data_file:         "Data",
             GMSB1_file: "$\Lambda 40 \\tan\\beta 30$",
             GMSB2_file: "$\Lambda 50 \\tan\\beta 40$",
             GMSB3_file: "$\Lambda 50 \\tan\\beta 20$"}

filenames3 = {data_periodB_file: "PeriodB",
          data_periodD_file: "PeriodD",
          data_periodE_file: "PeriodE",
          data_periodF_file: "PeriodF",
          data_periodG_file: "PeriodG",
          data_periodH_file: "PeriodH",
          data_periodI_file: "PeriodI",
          data_periodJ_file: "PeriodJ",
          data_periodK_file: "PeriodK",
          data_periodL_file: "PeriodL",
          data_periodM_file: "PeriodM"
          }


contents = "\\documentclass[12pt]{article}\n\\usepackage[landscape]{geometry}\n\\begin{document}\n\n \[ \left( \\begin{array}{c} N$^{Obs}_{W CR}$ \\ N$^{Obs}_{t CR}$  \\ N$^{Obs}_{Z CR}$  \end{array} \\right)\] = [ \left( \\begin{array}{ccc} W$_{W CR}$ & t$_{W CR}$ & Z$_{W CR}$ \\ W$_{top CR}$ & t$_{top CR}$ & Z$_{top CR}$  \\ W$_{Z CR}$ & t$_{Z CR}$ & Z$_{Z CR}$   \end{array} \\right)\] $\times$ S\\begin{center}\n\\begin{tabular}{|l|l"

for file1 in files1:
	contents += "|l"

contents += "}\n\\hline\n"

for file1 in files1:
   print filenames1[file1]
   contents += " & " + filenames1[file1]
contents += "\\\\\hline\n"

for cut in cutlist.cuts_ditau:
   print cut
   print cutlist.cutnames[cut]
   contents+=cutlist.cutnames[cut]
   for file1 in files1:
      contents += " " +  "&" + " " + evnum(cut,file1)
   contents += "\\\\\\hline\n"

contents += "\\end{tabular}\\end{center}"

print contents
table_file = open("matrix.tex", "w")
table_file.writelines(contents)
