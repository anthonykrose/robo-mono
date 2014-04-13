import ROOT
ROOT.gROOT.SetBatch()
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)
import cutlist
from optparse import OptionParser

def color(file):
	filename = str(file.GetName())
	if "pythia_jetjet" in filename:
		return ROOT.kYellow 
	elif "Dibosons" in filename:
		return ROOT.kGray
	elif "DY" in filename:
		return ROOT.kPink+1
	elif "Ttbar" in filename:
		return ROOT.kGreen-9
	elif "SingleT" in filename:
		return ROOT.kRed+3
	elif "Zjets" in filename:
		return ROOT.kAzure+1
	elif "Wjets" in filename:
		return ROOT.kGreen
	elif "WZGamma" in filename:
		return ROOT.kGreen
	else:
		return ROOT.kBlack

def plot(hist_name, cut, hist_min, hist_max, canvas, bkg_list, data, signal, signal_2, xrange=False, xmin=0, xmax=600):
	print hist_name + "_" + cutlist.cutindices[cut] + cut + ".png"
	hs1 = ROOT.THStack("hs1", "stack" + hist_name + cut)
	canvas.Clear()
	canvas.SetLogy()
	for file in bkg_list:
		print file.GetName()
		file.cd(); hist = file.Get(hist_name+cut); hist.SetFillColor(color(file)); hs1.Add(hist)
	hs1.Draw("hist")
	hs1.GetYaxis().SetTitle("Entries/10 GeV")
	hs1.SetMinimum(hist_min)
	hs1.SetMaximum(hist_max)
	if (xrange):
		hs1.GetXaxis().SetRangeUser(xmin,xmax)
	data.cd(); hist = data.Get(hist_name+cut); hist.SetLineColor(ROOT.kBlack); hist.SetMarkerStyle(20); hist.SetMarkerSize(0.5); hist.Draw("p e same"); 
	signal.cd(); hist = signal.Get(hist_name+cut); hist.SetLineColor(ROOT.kRed); hist.SetLineWidth(4);hist.Draw("same hist")
	signal_2.cd(); hist = signal_2.Get(hist_name+cut); hist.SetLineColor(ROOT.kBlue+3);hist.SetLineWidth(4); hist.Draw("same hist")
	legend.Draw("same")
	canvas.Print("~/plots6/" + hist_name + "_" + cutlist.cutindices[cut] + cut + ".png")

ROOT.gStyle.SetErrorX(0)
ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetTextSize(0.52)

parser = OptionParser()
parser.add_option("-l", "--lumi", dest="lumi", type = "string",
                  help="Luminosity", default = "5000.0")
(options, args) = parser.parse_args()

#ROOT.gROOT.LoadMacro("AtlasUtils.C")
#SM_file = new TFile("standard_model_reco_histos.root")
#SU4_file = ROOT.TFile("mc11_7TeV.106484.SU4_herwigpp_susy_TrilepCutflow_1127.1pb.root")

DG1_file = ROOT.TFile("mc11_7TeV.138429.DGemt_TB6_M12U_100_110_110_2L_jimmy_susy_TrilepCutflow_" + options.lumi + "pb.root")

DG2_file = ROOT.TFile("mc11_7TeV.138449.DGemt_TB6_M12U_100_160_100_2L_jimmy_susy_TrilepCutflow_" + options.lumi + "pb.root")




Ttbar_file = ROOT.TFile("Ttbar_TrilepCutflow_" + options.lumi + "pb.root")
SingleT_file = ROOT.TFile("SingleT_TrilepCutflow_" + options.lumi + "pb.root")
Wjets_file = ROOT.TFile("Wjets_TrilepCutflow_" + options.lumi + "pb.root")
Zjets_file = ROOT.TFile("Zjets_TrilepCutflow_" + options.lumi + "pb.root")
pythia_jetjet_file = ROOT.TFile("pythia_jetjet_TrilepCutflow_" + options.lumi + "pb.root")
Dibosons_file = ROOT.TFile("Dibosons_TrilepCutflow_" + options.lumi + "pb.root")
DY_file = ROOT.TFile("DY_TrilepCutflow_" + options.lumi + "pb.root")
WZGamma_file = ROOT.TFile("WZGamma_TrilepCutflow_" + options.lumi + "pb.root")
data_file = ROOT.TFile("Data.Combined.root")
legend = ROOT.TLegend(.65,.55,.85,.75) 
legend.SetFillColor(0) 
legend.SetMargin(0.5)


pythia_jetjet_file.cd(); hist = pythia_jetjet_file.Get("Mt_after_preselection"); legend.AddEntry(hist, "QCD") 
Ttbar_file.cd(); hist = Ttbar_file.Get("Mt_after_preselection"); legend.AddEntry(hist, "t#bar{t}")
SingleT_file.cd(); hist = SingleT_file.Get("Mt_after_preselection"); legend.AddEntry(hist, "single t")
Wjets_file.cd(); hist = Wjets_file.Get("Mt_after_preselection"); legend.AddEntry(hist, "W + jets")
Zjets_file.cd(); hist = Zjets_file.Get("Mt_after_preselection"); legend.AddEntry(hist, "Z + jets")
Dibosons_file.cd(); hist = Dibosons_file.Get("Mt_after_preselection"); legend.AddEntry(hist, "dibosons")
DY_file.cd(); hist = DY_file.Get("Mt_after_preselection"); legend.AddEntry(hist, "Drell Yan")
data_file.cd(); hist = data_file.Get("Mt_after_preselection"); legend.AddEntry(hist, "data")
DG1_file.cd(); hist = DG1_file.Get("Mt_after_preselection"); legend.AddEntry(hist, "DG1")
DG2_file.cd(); hist = DG2_file.Get("Mt_after_preselection"); legend.AddEntry(hist, "DG2")

#SU4_file.cd(); hist = SU4_file.Get("Mt_after_preselection"); legend.AddEntry(hist, "SU4")
#SU11_file.cd(); hist = SU11_file.Get("Mt_after_preselection"); legend.AddEntry(hist, "SU11")

#mycolors =  {ROOT.kRed, ROOT.kBlacROOT.k, ROOT.kBlue+1, ROOT.kBlue+3, ROOT.kBlue-4, ROOT.kGreen-8}
#myfillcol    = {ROOT.kGreen, ROOT.kGreen-9, ROOT.kGray, ROOT.kPink+1, ROOT.kAzure+1, ROOT.kYellow, ROOT.kWhite, ROOT.kWhite}
##Color_t myfillsty[6] = { 1001,    1001,   1001,  3003,   1001,    1001}
#mystyle  =  {1, 1, 1, 1, 1, 1}
#mywidth  =  {6, 1, 1, 1, 1, 1}

bkg_list = [
				Dibosons_file,
				DY_file,
				SingleT_file,
				Ttbar_file,
				Zjets_file,
				Wjets_file,
				pythia_jetjet_file
			  ]


c1 = ROOT.TCanvas("c1","Example",800,600)
plot("Mt", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Mt", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Mt", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Mt", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Mt", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Mt", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Mt", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Mt", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("MET", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file, True, 0, 900)
plot("MET", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file, True, 0, 900)
plot("MET", "_after_twolep", 0.1, 1e5, c1, bkg_list, data_file, DG1_file, DG2_file, True, 0, 900)
plot("MET", "_after_trilep", 0.1, 1e5, c1, bkg_list, data_file, DG1_file, DG2_file, True, 0, 900)
plot("MET", "_after_sfos", 0.1, 1e5, c1, bkg_list, data_file, DG1_file, DG2_file, True, 0, 900)
plot("MET", "_after_Zveto", 0.1, 1e5, c1, bkg_list, data_file, DG1_file, DG2_file, True, 0, 200)
plot("MET", "_after_bjet_veto", 0.1, 1e5, c1, bkg_list, data_file, DG1_file, DG2_file, True, 0, 200)
plot("MET", "_after_MET_g50", 0.1, 1e5, c1, bkg_list, data_file, DG1_file, DG2_file, True, 0, 200)

plot("Meff", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Meff", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Meff", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Meff", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Meff", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Meff", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Meff", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Meff", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("Elec_N", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_N", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_N", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_N", "_after_trilep", 0.1, 1e5, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_N", "_after_sfos", 0.1, 1e5, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_N", "_after_Zveto", 0.1, 1e5, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_N", "_after_bjet_veto", 0.1, 1e5, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_N", "_after_MET_g50", 0.1, 1e5, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("Elec_Pt", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_Pt", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_Pt", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_Pt", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_Pt", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_Pt", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_Pt", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Elec_Pt", "_after_MET_g50", 0.1, 1e5, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("Muon_N", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_N", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_N", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_N", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_N", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_N", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_N", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_N", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("Muon_Pt", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_Pt", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_Pt", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_Pt", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_Pt", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_Pt", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_Pt", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Muon_Pt", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("Lep_N", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_N", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_N", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_N", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_N", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_N", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_N", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_N", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("Lep_Pt", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_Pt", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_Pt", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_Pt", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_Pt", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_Pt", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_Pt", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Lep_Pt", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("Track_N", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_N", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_N", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_N", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_N", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_N", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_N", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_N", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("Track_Pt", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_Pt", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_Pt", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_Pt", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_Pt", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_Pt", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_Pt", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_Pt", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)


plot("Track_PtCone20", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("Track_PtCone20_over_Pt", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20_over_Pt", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20_over_Pt", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20_over_Pt", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20_over_Pt", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20_over_Pt", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20_over_Pt", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone20_over_Pt", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("Track_PtCone30", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("Track_PtCone30_over_Pt", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30_over_Pt", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30_over_Pt", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30_over_Pt", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30_over_Pt", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30_over_Pt", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30_over_Pt", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone30_over_Pt", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("Track_PtCone40", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("Track_PtCone40_over_Pt", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40_over_Pt", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40_over_Pt", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40_over_Pt", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40_over_Pt", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40_over_Pt", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40_over_Pt", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("Track_PtCone40_over_Pt", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)


plot("MElecElec", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MElecElec", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MElecElec", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MElecElec", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MElecElec", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MElecElec", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MElecElec", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MElecElec", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("MMuonMuon", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MMuonMuon", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MMuonMuon", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MMuonMuon", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MMuonMuon", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MMuonMuon", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MMuonMuon", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MMuonMuon", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("MLepLepLep", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepLep", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepLep", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepLep", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepLep", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepLep", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepLep", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepLep", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("MLepLep", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLep", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLep", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLep", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLep", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLep", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLep", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLep", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("MLepTau", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTau", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTau", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTau", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTau", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTau", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTau", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTau", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("MLepTrack", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTrack", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTrack", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTrack", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTrack", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTrack", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTrack", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepTrack", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("MLepLepTrack", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTrack", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTrack", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTrack", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTrack", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTrack", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTrack", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTrack", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("MLepSignalTrack", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepSignalTrack", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepSignalTrack", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepSignalTrack", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepSignalTrack", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepSignalTrack", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepSignalTrack", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepSignalTrack", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("MLepLepSignalTrack", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepSignalTrack", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepSignalTrack", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepSignalTrack", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepSignalTrack", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepSignalTrack", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepSignalTrack", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepSignalTrack", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("MLepLepTau", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTau", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTau", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTau", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTau", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTau", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTau", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("MLepLepTau", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("SignalTrack_N", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_N", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_N", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_N", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_N", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_N", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_N", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_N", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)

plot("SignalTrack_Pt", "_after_preselection", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_Pt", "_after_onelep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_Pt", "_after_twolep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_Pt", "_after_trilep", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_Pt", "_after_sfos", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_Pt", "_after_Zveto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_Pt", "_after_bjet_veto", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
plot("SignalTrack_Pt", "_after_MET_g50", 0.1, 1e7, c1, bkg_list, data_file, DG1_file, DG2_file)
