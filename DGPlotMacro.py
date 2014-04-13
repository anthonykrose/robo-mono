import ROOT
from DGFiles import *
import cutlist
from math import log,sqrt

ROOT.gROOT.SetBatch()
c1 = ROOT.TCanvas("c1","Example",800,600)

def Z(S, B):
   return sqrt(2*((S+B)*log(1.0+S/B)-S))

def gridplot_N(hist_name, cut, index, file_list, output_hist_name, c1): 
	output_hist = ROOT.TH2F(output_hist_name,"" ,16,100.,260.,16,100.,260.)
	for file in file_list:
		#print file.GetName() + hist_name + "_" + cut
		output_hist.Fill(points[file][0],points[file][1],round(file.Get(hist_name + "_" + cut).GetBinContent(1),1))	
	ROOT.gStyle.SetPalette(1)
	ROOT.gStyle.SetOptStat(0)
	output_hist.SetXTitle("M_{2}")
	output_hist.SetYTitle("M_{U}")
	output_hist.GetZaxis().SetRangeUser(0,300)
	output_hist.Draw("COLZ TEXT")
	c1.Print("~/plots/" + output_hist_name+ "_" + str(index) + "_"  + cut + ".png")

def gridplot_mean(hist_name, cut, index, file_list, output_hist_name, c1): 
	output_hist = ROOT.TH2F(output_hist_name,"" ,16,100.,260.,16,100.,260.)
	for file in file_list:
		output_hist.Fill(points[file][0],points[file][1],round(file.Get(hist_name + "_" + cut).GetMean(),1))	
	ROOT.gStyle.SetPalette(1)
	ROOT.gStyle.SetOptStat(0)
	output_hist.GetZaxis().SetRangeUser(0,100)
	output_hist.SetXTitle("M_{2}")
	output_hist.SetYTitle("M_{U}")
	output_hist.Draw("COLZ TEXT")
	c1.Print("~/plots/" + output_hist_name+ "_" + str(index) + "_"  + cut + ".png")

def gridplot_2N(hist_name1, hist_name2, file_list, output_hist_name, c1): 
	output_hist = ROOT.TH2F(output_hist_name,"" ,16,100.,260.,16,100.,260.)
	for file in file_list:
		h1 = file.Get(hist_name1).GetBinContent(1)
		h2 = file.Get(hist_name2).GetBinContent(1)
#		print file.GetName() + hist_name + "_" + cut
		output_hist.Fill(points[file][0],points[file][1],round(100*h2/h1,1))
	ROOT.gStyle.SetPalette(1)
	ROOT.gStyle.SetOptStat(0)
	output_hist.SetXTitle("M_{2}")
	output_hist.SetYTitle("M_{U}")
	output_hist.GetZaxis().SetRangeUser(0,300)
	output_hist.Draw("COLZ TEXT")
	c1.Print(output_hist_name+ ".png")

def gridplot_2SUM(hist_name1, hist_name2, file_list, output_hist_name, c1): 
	output_hist = ROOT.TH2F(output_hist_name,"" ,16,100.,260.,16,100.,260.)
	for file in file_list:
		h1 = file.Get(hist_name1).GetBinContent(1)
		h2 = file.Get(hist_name2).GetBinContent(1)
#		print file.GetName() + hist_name + "_" + cut
		output_hist.Fill(points[file][0],points[file][1],round(h2+h1,1))
	ROOT.gStyle.SetPalette(1)
	ROOT.gStyle.SetOptStat(0)
	output_hist.SetXTitle("M_{2}")
	output_hist.SetYTitle("M_{U}")
	output_hist.GetZaxis().SetRangeUser(0,300)
	output_hist.Draw("COLZ TEXT")
	c1.Print(output_hist_name+ ".png")

#GRID100 = ROOT.TH2F ("GRID100","" ,16,100.,260.,16,100.,260.)
#for file in M1_100:
#	GRID100.Fill(points[file][0],points[file][1],round(file.Get("Event_N_after_etmiss50").GetBinContent(1),1))	
#SetPlotStyle();
#MC_file = ROOT.TFile("MC_1000.0pb.root");
multiplicities = ["Event_N", "Elec_N", "Muon_N", "Tau_N", "Lep_N", "Jet_N", "Bjet_N", "Track_N", "SignalTrack_N"]

pTs = ["Elec_Pt", "Muon_Pt", "Tau_Pt", "Lep_Pt", "Jet_Pt", "Track_Pt","SignalTrack_Pt"]

for (i,cut) in enumerate(cutlist.cuts_no_flavour): 
	print cut
	gridplot_N("Event_N",cut, i, M1_100, "M1_100_" + "Event_N", c1)
	gridplot_N("Event_N",cut, i, M1_140, "M1_140_" + "Event_N", c1)
	gridplot_N("Event_N",cut, i, M1_250, "M1_250_" + "Event_N", c1)

#gridplot_2N("Event_N_after_true_trilep", "Event_N_after_one_true_track", M1_100, "M1_100_" + "Event_N_trilep_or_track", c1)
#gridplot_2N("Event_N_after_true_trilep", "Event_N_after_one_true_track", M1_140, "M1_140_" + "Event_N_trilep_or_track", c1)
#gridplot_2N("Event_N_after_true_trilep", "Event_N_after_one_true_track", M1_250, "M1_250_" + "Event_N_trilep_or_track", c1)
#
#gridplot_2SUM("Event_N_after_true_trilep", "Event_N_after_one_true_track", M1_100, "M1_100_" + "Event_N_trilep_sum_track", c1)
#gridplot_2SUM("Event_N_after_true_trilep", "Event_N_after_one_true_track", M1_140, "M1_140_" + "Event_N_trilep_sum_track", c1)
#gridplot_2SUM("Event_N_after_true_trilep", "Event_N_after_one_true_track", M1_250, "M1_250_" + "Event_N_trilep_sum_track", c1)


	for dist in multiplicities:
		gridplot_mean(dist,cut, i, M1_100, "M1_100_" + dist, c1)
		gridplot_mean(dist,cut, i, M1_140, "M1_140_" + dist, c1)
		gridplot_mean(dist,cut, i, M1_250, "M1_250_" + dist, c1)
	for pT in pTs:
		gridplot_mean(pT,cut, i, M1_100, "M1_100_" + pT, c1)
		gridplot_mean(pT,cut, i, M1_140, "M1_140_" + pT, c1)
		gridplot_mean(pT,cut, i, M1_250, "M1_250_" + pT, c1)
	gridplot_mean("MET",cut, i, M1_100, "M1_100_" + "MET", c1)
	gridplot_mean("MET",cut, i, M1_140, "M1_140_" + "MET", c1)
	gridplot_mean("MET",cut, i, M1_250, "M1_250_" + "MET", c1)
	gridplot_mean("Meff",cut, i, M1_100, "M1_100_" + "Meff", c1)
	gridplot_mean("Meff",cut, i, M1_140, "M1_140_" + "Meff", c1)
	gridplot_mean("Meff",cut, i, M1_250, "M1_250_" + "Meff", c1)


#gridplot_N("Event_N","after_true_trilep", 0, M1_100, "M1_100_" + "Event_N", c1)
#gridplot_N("Event_N","after_true_trilep", 0, M1_140, "M1_140_" + "Event_N", c1)
#gridplot_N("Event_N","after_true_trilep", 0, M1_250, "M1_250_" + "Event_N", c1)

#gridplot_N("Event_N","after_one_true_tau", 0, M1_100, "M1_100_" + "Event_N", c1)
#gridplot_N("Event_N","after_one_true_tau", 0, M1_140, "M1_140_" + "Event_N", c1)
#gridplot_N("Event_N","after_one_true_tau", 0, M1_250, "M1_250_" + "Event_N", c1)

	
	#gridplot_Z("Event_N_after_"+cut, M1_100, "M1_100_Z_"+cut, MC_file, c1)
	#gridplot_Z("Event_N_after_"+cut, M1_140, "M1_140_Z_"+cut, MC_file, c1)
	#gridplot_Z("Event_N_after_"+cut, M1_250, "M1_250_Z_"+cut, MC_file, c1)


#c1->SetLogz()
