#program to plot the event yield of grids
import ROOT
from ROOT import TH1F, TStyle, TGString, TROOT, TH2F, THStack, TDirectory, TFile, TKey, TEnv, TAxis, THashList, TIterator, TObjString, TTree, TCanvas, gROOT, gRandom
from cutList import *
from gridPoints import *
from math import log,sqrt

ROOT.gROOT.SetBatch()

c1 = ROOT.TCanvas("c1","Example",800,600)
c1.cd()
#print "in canvas"

def gridplot_N ( cut, index, grid_list, output_hist_name, c1, tauID, mass_points):

   output_hist = ROOT.TH2F(cut,"" ,80,100.,800.,65,0.,650.) #define an output histogram
   graph=ROOT.TGraph2D(output_hist)
   graph.SetHistogram(output_hist)

   ROOT.gStyle.SetPalette(1)
   ROOT.gStyle.SetOptStat(0)
   output_hist.SetXTitle("m_\chi1^{+-}")
   output_hist.SetYTitle("m_\chi1^{0}")
                              

   for i in range(0,len(grid_list)):
      grid_point=grid_list[i]
      hist1=grid_point.Get(cut)
      sum1=hist1.GetSum()

      #print sum1
      if sum1!=0:
         output_hist.Fill(mass_points[grid_point][0],mass_points[grid_point][1],round(sum1,1))
         graph.SetPoint(i, mass_points[grid_point][0],mass_points[grid_point][1],round(sum1,1))
      else:
         output_hist.Fill(0.0, 0.0)
         graph.SetPoint(i, 0.0, 0.0, 0.0)

         
   #ROOT.gStyle.SetPalette(1)
   #ROOT.gStyle.SetOptStat(0)
   
   #graph.GetZaxis().SetTitle("N")
   #graph.GetXaxis().SetTitle("m_{1/2} [GeV]")
   #graph.GetYaxis().SetTitle("m_{0} [GeV]")
   #gra
   #output_hist.SetTitle("EventYield_"+cut)
   #output_hist.SetXTitle("m_\chi1^{+-}")
   #output_hist.SetYTitle("m_\chi1^{0}")
   #output_hist.GetZaxis().SetRangeUser(0.0,44.6)
   #  output_hist.Draw("COLZ")       


   graph.Draw("TEXT COLZ")
   c1.Print("png_files/"+output_hist_name+cut+tauID+".png")
   c1.Print("eps_files/"+output_hist_name+cut+tauID+".eps")

   
   hFile=ROOT.TFile("root_files/"+output_hist_name+cut+tauID+".root","RECREATE")
   hFile.cd()
   output_hist.Write()
   hFile.Close()


tauID="Tight"

for (i,cut) in enumerate(new_cuts):  #to be all united under cuts
   gridplot_N(cut, i, gridA ,"ModeAwSL", c1, tauID , mass_pointsA)

