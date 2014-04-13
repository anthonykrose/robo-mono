from optparse import OptionParser
import re, string
import sys, os, commands
import pickle
from ROOT import TFile, TTree, gROOT, gDirectory

gROOT.SetBatch(True)

emt_87_210 = TFile("SR_histos_emt_87_210.root")

files = [emt_87_210]

filenames= {emt_87_210	:"emt_87_210"} 


for file in files:
    event_histo = gDirectory.Get("EventN")
    event_count = event_histo.GetBinContent(2)
    event_error = event_histo.GetBinError(2)
    print filenames[file] + ' events = ' + str(round(event_count,2)) + ' +/- ' + str(round(event_error,2))
