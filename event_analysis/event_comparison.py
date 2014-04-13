#!/usr/bin/env python
from xsec import *
from optparse import OptionParser
import re, string
import sys, os, commands
import pickle
from ROOT import TFile, TTree, gROOT, gDirectory


gROOT.SetBatch(True)

def reweight_factor(infile, lumi):
	m = re.search('MC\.......',infile.GetName())
	try:
		cross_section =  cross_sections[m.group(0)]
	except KeyError:
		print "Error: cross section for ", infile.GetName(), " not found"
		return 0
	event_histo = gDirectory.Get("Event_N_initial_lepSF_pileupSF")
	print infile.GetName()
	#event_histo = gDirectory.Get("Event_N_initial")
	event_count = event_histo.GetBinContent(1)
	if event_count == 0:
		print "Error: zero events in MC, no reweighting applied"
		return 0
	event_count = event_histo.GetBinContent(1)
	return (float(lumi)*cross_section)/event_count

def full_overlap(infilename, true):
	if not "MC" in infilename:
		print "Error: filename does not contain MC"
		return {infilename:None}
	if infilename == None:
		return {infilename:None}
	print infilename
	prefix=""
	prefix2=""
	if true:
		prefix="True"
		prefix2="True"
	else:
		prefix="Fake"
		prefix2="False"
	
	events = [prefix+ " trilepton",prefix + " tau", prefix2+ " track"]
	evcounts = []
	infile = TFile(infilename, "readonly")
	for (i, evt) in enumerate(events):
		cmd_str="grep \"" + evt + " event\" " + infilename.replace(".root",".txt") + " | sed \'s/.*event in//\'"
		print cmd_str
		evcount = commands.getoutput(cmd_str).split("\n")
		if evcount == ['']:
			evcount = []
		#print infilename, prefix, len(evcount)
		#print evcount
		evcounts.append(evcount)

	sf = reweight_factor(infile, options.lumi)
	len0 =len(evcounts[0])
	len1 =len(evcounts[1])
	len2 =len(evcounts[2])

	return [len0,len1,len2, 
			  get_overlap(evcounts[0], evcounts[1]), get_overlap(evcounts[1], evcounts[2]),
			  get_overlap(evcounts[0], evcounts[2]), sf]

def get_overlap(events1, events2):
	#return list(set(events1) & set(events2))
	overlap=[]
	#print "get_overlap", events1, events2
	#if events1 == ['']:
	##	print "get_overlap 0"
	#	return 0
	#if events2 == ['']:
	##	print "get_overlap 0"
	#	return 0
	for ev1 in events1:
		if ev1 in events2:
			overlap.append(ev1)
	#print "Overlap: ", overlap, len(overlap)
	return len(overlap)
		
def overlap_table(trilep, tau, track, scale=1):
	return_str = "\\begin{table}\n"
	return_str +="\\begin{tabular}{|l|l|l|l|}\n"
	return_str +="\\hline\n"
	return_str +=          "& Trilepton & 2 $\ell$ + $\\tau$      & 2 $\\ell$ + track \\\\ \hline\n"
	return_str +="Trilepton & " + str(round((len(trilep))*scale, 1)) + " & " + str(round(get_overlap(trilep,tau)*scale,1)) + " & " + str(round(get_overlap(trilep,track)*scale,1))  + "\\\\ \\hline\n"
	return_str +="2 $\\ell$ + $\\tau$&\\cellcolor[gray]{0.9} & " + str(round((len(tau))*scale,1)) +  " & " + str(round(get_overlap(tau,track)*scale,1)) + "\\\\ \\hline\n"
	return_str +="2 $\\ell$ + track&\\cellcolor[gray]{0.9}   & \cellcolor[gray]{0.9} & " + str(round((len(track))*scale,1)) + " \\\\\n"
	return_str +="\\hline\n"
	return_str +="\\end{tabular}\n"
	return_str +="\\end{table}\n"
	return return_str

def overlap_table(trilep, tau, track, trileptau, trileptrack, tautrack):
	return_str = "\\begin{table}\n"
	return_str +="\\begin{tabular}{|l|l|l|l|}\n"
	return_str +="\\hline\n"
	return_str +=          "& Trilepton & 2 $\ell$ + $\\tau$      & 2 $\\ell$ + track \\\\ \hline\n"
	return_str +="Trilepton & " + str(round(trilep, 1)) + " & " + str(round(trileptau,1)) + " & " + str(round(trileptrack,1))  + "\\\\ \\hline\n"
	return_str +="2 $\\ell$ + $\\tau$&\\cellcolor[gray]{0.9} & " + str(round(tau,1)) +  " & " + str(round(tautrack,1)) + "\\\\ \\hline\n"
	return_str +="2 $\\ell$ + track&\\cellcolor[gray]{0.9}   & \cellcolor[gray]{0.9} & " + str(round(track,1)) + " \\\\\n"
	return_str +="\\hline\n"
	return_str +="\\end{tabular}\n"
	return_str +="\\end{table}\n"
	return return_str


parser = OptionParser()
parser.add_option("-l", "--lumi", dest="lumi", type = "float",
                  help="Luminosity to rescale to (pb^-1)", default = 1000)
#parser.add_option("-o", "--overwrite", dest="overwrite",
#                  help="Overwrite original file", default = False)
#parser.add_option("-x", "--exclude", dest="exclude",
#						help="String to exclude")
(options, args) = parser.parse_args()

print args


pythia_jetjet = ["MC.105009.J0_doTruthMatch_10GeVTrk.root", "MC.105010.J1_doTruthMatch_10GeVTrk.root", "MC.105011.J2_doTruthMatch_10GeVTrk.root", "MC.105012.J3_doTruthMatch_10GeVTrk.root", "MC.105013.J4_doTruthMatch_10GeVTrk.root", "MC.105014.J5_doTruthMatch_10GeVTrk.root", "MC.105015.J6_doTruthMatch_10GeVTrk.root", "MC.105016.J7_doTruthMatch_10GeVTrk.root", "MC.105017.J8_doTruthMatch_10GeVTrk.root"]
Ttbar = ["MC.105200.T1_McAtNlo_doTruthMatch_10GeVTrk.root", "MC.105204.TTbar_FullHad_McAtNlo_doTruthMatch_10GeVTrk.root"]
SingleT = ["MC.108340.st_tchan_enu_McAtNlo_doTruthMatch_10GeVTrk.root", "MC.108341.st_tchan_munu_McAtNlo_doTruthMatch_10GeVTrk.root", "MC.108342.st_tchan_taunu_McAtNlo_doTruthMatch_10GeVTrk.root", "MC.108343.st_schan_enu_McAtNlo_doTruthMatch_10GeVTrk.root", "MC.108344.st_schan_munu_McAtNlo_doTruthMatch_10GeVTrk.root", "MC.108345.st_schan_taunu_McAtNlo_doTruthMatch_10GeVTrk.root", "MC.108346.st_Wt_McAtNlo_doTruthMatch_10GeVTrk.root"]
Top = Ttbar + SingleT
Dibosons = ["MC.105986.ZZ_Herwig_doTruthMatch_10GeVTrk.root", "MC.105987.WZ_Herwig_doTruthMatch_10GeVTrk.root", "MC.105985.WW_Herwig_doTruthMatch_10GeVTrk.root"]
Zjets = ["MC.107650.AlpgenJimmyZeeNp0_doTruthMatch_10GeVTrk.root", "MC.107651.AlpgenJimmyZeeNp1_doTruthMatch_10GeVTrk.root", "MC.107652.AlpgenJimmyZeeNp2_doTruthMatch_10GeVTrk.root", "MC.107653.AlpgenJimmyZeeNp3_doTruthMatch_10GeVTrk.root", "MC.107654.AlpgenJimmyZeeNp4_doTruthMatch_10GeVTrk.root", "MC.107655.AlpgenJimmyZeeNp5_doTruthMatch_10GeVTrk.root", "MC.107660.AlpgenJimmyZmumuNp0_doTruthMatch_10GeVTrk.root", "MC.107661.AlpgenJimmyZmumuNp1_doTruthMatch_10GeVTrk.root", "MC.107662.AlpgenJimmyZmumuNp2_doTruthMatch_10GeVTrk.root", "MC.107663.AlpgenJimmyZmumuNp3_doTruthMatch_10GeVTrk.root", "MC.107664.AlpgenJimmyZmumuNp4_doTruthMatch_10GeVTrk.root", "MC.107665.AlpgenJimmyZmumuNp5_doTruthMatch_10GeVTrk.root", "MC.107670.AlpgenJimmyZtautauNp0_doTruthMatch_10GeVTrk.root", "MC.107671.AlpgenJimmyZtautauNp1_doTruthMatch_10GeVTrk.root", "MC.107672.AlpgenJimmyZtautauNp2_doTruthMatch_10GeVTrk.root", "MC.107673.AlpgenJimmyZtautauNp3_doTruthMatch_10GeVTrk.root", "MC.107674.AlpgenJimmyZtautauNp4_doTruthMatch_10GeVTrk.root", "MC.107675.AlpgenJimmyZtautauNp5_doTruthMatch_10GeVTrk.root", "MC.109300.AlpgenJimmyZeebbNp0_nofilter_doTruthMatch_10GeVTrk.root", "MC.109301.AlpgenJimmyZeebbNp1_nofilter_doTruthMatch_10GeVTrk.root", "MC.109302.AlpgenJimmyZeebbNp2_nofilter_doTruthMatch_10GeVTrk.root", "MC.109303.AlpgenJimmyZeebbNp3_nofilter_doTruthMatch_10GeVTrk.root", "MC.109305.AlpgenJimmyZmumubbNp0_nofilter_doTruthMatch_10GeVTrk.root", "MC.109306.AlpgenJimmyZmumubbNp1_nofilter_doTruthMatch_10GeVTrk.root", "MC.109307.AlpgenJimmyZmumubbNp2_nofilter_doTruthMatch_10GeVTrk.root", "MC.109308.AlpgenJimmyZmumubbNp3_nofilter_doTruthMatch_10GeVTrk.root", "MC.109310.AlpgenJimmyZtautaubbNp0_nofilter_doTruthMatch_10GeVTrk.root", "MC.109311.AlpgenJimmyZtautaubbNp1_nofilter_doTruthMatch_10GeVTrk.root", "MC.109312.AlpgenJimmyZtautaubbNp2_nofilter_doTruthMatch_10GeVTrk.root", "MC.109313.AlpgenJimmyZtautaubbNp3_nofilter_doTruthMatch_10GeVTrk.root"]
Wjets = ["MC.106280.AlpgenJimmyWbbNp0_doTruthMatch_10GeVTrk.root", "MC.106281.AlpgenJimmyWbbNp1_doTruthMatch_10GeVTrk.root", "MC.106282.AlpgenJimmyWbbNp2_doTruthMatch_10GeVTrk.root", "MC.106283.AlpgenJimmyWbbNp3_doTruthMatch_10GeVTrk.root", "MC.107680.AlpgenJimmyWenuNp0_doTruthMatch_10GeVTrk.root", "MC.107681.AlpgenJimmyWenuNp1_doTruthMatch_10GeVTrk.root", "MC.107682.AlpgenJimmyWenuNp2_doTruthMatch_10GeVTrk.root", "MC.107683.AlpgenJimmyWenuNp3_doTruthMatch_10GeVTrk.root", "MC.107684.AlpgenJimmyWenuNp4_doTruthMatch_10GeVTrk.root", "MC.107685.AlpgenJimmyWenuNp5_doTruthMatch_10GeVTrk.root", "MC.107690.AlpgenJimmyWmunuNp0_doTruthMatch_10GeVTrk.root", "MC.107691.AlpgenJimmyWmunuNp1_doTruthMatch_10GeVTrk.root", "MC.107692.AlpgenJimmyWmunuNp2_doTruthMatch_10GeVTrk.root", "MC.107693.AlpgenJimmyWmunuNp3_doTruthMatch_10GeVTrk.root", "MC.107694.AlpgenJimmyWmunuNp4_doTruthMatch_10GeVTrk.root", "MC.107695.AlpgenJimmyWmunuNp5_doTruthMatch_10GeVTrk.root", "MC.107700.AlpgenJimmyWtaunuNp0_doTruthMatch_10GeVTrk.root", "MC.107701.AlpgenJimmyWtaunuNp1_doTruthMatch_10GeVTrk.root", "MC.107702.AlpgenJimmyWtaunuNp2_doTruthMatch_10GeVTrk.root", "MC.107703.AlpgenJimmyWtaunuNp3_doTruthMatch_10GeVTrk.root", "MC.107704.AlpgenJimmyWtaunuNp4_doTruthMatch_10GeVTrk.root", "MC.107705.AlpgenJimmyWtaunuNp5_doTruthMatch_10GeVTrk.root"]
DY = ["MC.116250.AlpgenJimmyZeeNp0_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116251.AlpgenJimmyZeeNp1_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116252.AlpgenJimmyZeeNp2_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116253.AlpgenJimmyZeeNp3_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116254.AlpgenJimmyZeeNp4_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116255.AlpgenJimmyZeeNp5_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116260.AlpgenJimmyZmumuNp0_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116261.AlpgenJimmyZmumuNp1_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116262.AlpgenJimmyZmumuNp2_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116263.AlpgenJimmyZmumuNp3_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116264.AlpgenJimmyZmumuNp4_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116265.AlpgenJimmyZmumuNp5_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116270.AlpgenJimmyZtautauNp0_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116271.AlpgenJimmyZtautauNp1_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116272.AlpgenJimmyZtautauNp2_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116273.AlpgenJimmyZtautauNp3_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116274.AlpgenJimmyZtautauNp4_Mll10to40_doTruthMatch_10GeVTrk.root", "MC.116275.AlpgenJimmyZtautauNp5_Mll10to40_doTruthMatch_10GeVTrk.root"]

#MC = Ttbar + SingleT + Dibosons + Zjets + Wjets + DY
MC = pythia_jetjet + Ttbar + SingleT + Dibosons + Zjets + Wjets + DY
#MC = pythia_jetjet# + Ttbar + SingleT + Dibosons + Zjets + Wjets + DY
#MC = Dibosons + DY
MCTrueDict = {} 
MCFakeDict = {} 
for file in MC:
	MCTrueDict[file]=full_overlap(file,True)
	MCFakeDict[file]=full_overlap(file,False)
#print MCTrueDict	
sum_trilep=0
sum_tau=0
sum_track=0
trilep_tau=0
tau_track=0
trilep_track=0
	
for file in MC:
	sum_trilep +=MCTrueDict[file][0]*MCTrueDict[file][6]
	sum_tau +=MCTrueDict[file][1]*MCTrueDict[file][6]
	sum_track +=MCTrueDict[file][2]*MCTrueDict[file][6]
	trilep_tau +=MCTrueDict[file][3]*MCTrueDict[file][6]
	tau_track +=MCTrueDict[file][4]*MCTrueDict[file][6]
	trilep_track +=MCTrueDict[file][5]*MCTrueDict[file][6]

#print 'sum_trilep '   , sum_trilep
#print 'sum_tau '      , sum_tau
#print 'sum_track '    , sum_track
#print 'trilep_tau '   , trilep_tau
#print 'tau_track '    , tau_track
#print 'trilep_track ' , trilep_track
print "\\begin{frame}\nMC True"
print overlap_table(sum_trilep, sum_tau, sum_track, trilep_tau,  trilep_track, tau_track)

mc_true_pickle = open("mcTrue.p", "wb")
pickle.dump(MCTrueDict, mc_true_pickle)

sum_trilep=0
sum_tau=0
sum_track=0
trilep_tau=0
tau_track=0
trilep_track=0
	
for file in MC:
	sum_trilep +=MCFakeDict[file][0]*MCFakeDict[file][6]
	sum_tau +=MCFakeDict[file][1]*MCFakeDict[file][6]
	sum_track +=MCFakeDict[file][2]*MCFakeDict[file][6]
	trilep_tau +=MCFakeDict[file][3]*MCFakeDict[file][6]
	tau_track +=MCFakeDict[file][4]*MCFakeDict[file][6]
	trilep_track +=MCFakeDict[file][5]*MCFakeDict[file][6]

#print 'sum_trilep '   , sum_trilep
#print 'sum_tau '      , sum_tau
#print 'sum_track '    , sum_track
#print 'trilep_tau '   , trilep_tau
#print 'tau_track '    , tau_track
#print 'trilep_track ' , trilep_track

print "MC Fake"
print overlap_table(sum_trilep, sum_tau, sum_track, trilep_tau,  trilep_track, tau_track)
print "\\end{frame}"

#for file in MC:
#	print "\\begin{frame}\nTrue ", file
#	sum_trilep = MCTrueDict[file][0]*MCTrueDict[file][6]
#	sum_tau = MCTrueDict[file][1]*MCTrueDict[file][6]
#	sum_track = MCTrueDict[file][2]*MCTrueDict[file][6]
#	trilep_tau = MCTrueDict[file][3]*MCTrueDict[file][6]
#	tau_track = MCTrueDict[file][4]*MCTrueDict[file][6]
#	trilep_track = MCTrueDict[file][5]*MCTrueDict[file][6]
#	print overlap_table(sum_trilep, sum_tau, sum_track, trilep_tau,  trilep_track, tau_track)
#
#for file in MC:
#	print "Fake ", file
#	sum_trilep = MCFakeDict[file][0]*MCFakeDict[file][6]
#	sum_tau = MCFakeDict[file][1]*MCFakeDict[file][6]
#	sum_track = MCFakeDict[file][2]*MCFakeDict[file][6]
#	trilep_tau = MCFakeDict[file][3]*MCFakeDict[file][6]
#	tau_track = MCFakeDict[file][4]*MCFakeDict[file][6]
#	trilep_track = MCFakeDict[file][5]*MCFakeDict[file][6]
#	print overlap_table(sum_trilep, sum_tau, sum_track, trilep_tau,  trilep_track, tau_track)
#	print "\\end{frame}"

mc_fake_pickle = open("mc_fake.p", "wb")
pickle.dump(MCFakeDict, mc_fake_pickle)

MC = ['MC.138421.DGemt_TB6_M12U_100_100_100_doTruthMatch_10GeVTrk.root',
      'MC.138422.DGemt_TB6_M12U_100_100_110_doTruthMatch_10GeVTrk.root',
      'MC.138423.DGemt_TB6_M12U_100_100_120_doTruthMatch_10GeVTrk.root',
      'MC.138424.DGemt_TB6_M12U_100_100_140_doTruthMatch_10GeVTrk.root',
      'MC.138425.DGemt_TB6_M12U_100_100_160_doTruthMatch_10GeVTrk.root',
      'MC.138426.DGemt_TB6_M12U_100_100_180_doTruthMatch_10GeVTrk.root',
      'MC.138427.DGemt_TB6_M12U_100_100_250_doTruthMatch_10GeVTrk.root',
      'MC.138428.DGemt_TB6_M12U_100_110_100_doTruthMatch_10GeVTrk.root',
      'MC.138429.DGemt_TB6_M12U_100_110_110_doTruthMatch_10GeVTrk.root',
      'MC.138430.DGemt_TB6_M12U_100_110_120_doTruthMatch_10GeVTrk.root',
      'MC.138431.DGemt_TB6_M12U_100_110_140_doTruthMatch_10GeVTrk.root',
      'MC.138432.DGemt_TB6_M12U_100_110_160_doTruthMatch_10GeVTrk.root',
      'MC.138433.DGemt_TB6_M12U_100_110_180_doTruthMatch_10GeVTrk.root',
      'MC.138434.DGemt_TB6_M12U_100_110_250_doTruthMatch_10GeVTrk.root',
      'MC.138435.DGemt_TB6_M12U_100_120_100_doTruthMatch_10GeVTrk.root',
      'MC.138436.DGemt_TB6_M12U_100_120_110_doTruthMatch_10GeVTrk.root',
      'MC.138437.DGemt_TB6_M12U_100_120_120_doTruthMatch_10GeVTrk.root',
      'MC.138438.DGemt_TB6_M12U_100_120_140_doTruthMatch_10GeVTrk.root',
      'MC.138439.DGemt_TB6_M12U_100_120_160_doTruthMatch_10GeVTrk.root',
      'MC.138440.DGemt_TB6_M12U_100_120_180_doTruthMatch_10GeVTrk.root',
      'MC.138441.DGemt_TB6_M12U_100_120_250_doTruthMatch_10GeVTrk.root',
      'MC.138442.DGemt_TB6_M12U_100_140_100_doTruthMatch_10GeVTrk.root',
      'MC.138443.DGemt_TB6_M12U_100_140_110_doTruthMatch_10GeVTrk.root',
      'MC.138444.DGemt_TB6_M12U_100_140_120_doTruthMatch_10GeVTrk.root',
      'MC.138445.DGemt_TB6_M12U_100_140_140_doTruthMatch_10GeVTrk.root',
      'MC.138446.DGemt_TB6_M12U_100_140_160_doTruthMatch_10GeVTrk.root',
      'MC.138447.DGemt_TB6_M12U_100_140_180_doTruthMatch_10GeVTrk.root',
      'MC.138448.DGemt_TB6_M12U_100_140_250_doTruthMatch_10GeVTrk.root',
      'MC.138449.DGemt_TB6_M12U_100_160_100_doTruthMatch_10GeVTrk.root',
      'MC.138450.DGemt_TB6_M12U_100_160_110_doTruthMatch_10GeVTrk.root',
      'MC.138451.DGemt_TB6_M12U_100_160_120_doTruthMatch_10GeVTrk.root',
      'MC.138452.DGemt_TB6_M12U_100_160_140_doTruthMatch_10GeVTrk.root',
      'MC.138453.DGemt_TB6_M12U_100_160_160_doTruthMatch_10GeVTrk.root',
      'MC.138454.DGemt_TB6_M12U_100_160_180_doTruthMatch_10GeVTrk.root',
      'MC.138455.DGemt_TB6_M12U_100_160_250_doTruthMatch_10GeVTrk.root',
      'MC.138456.DGemt_TB6_M12U_100_180_100_doTruthMatch_10GeVTrk.root',
      'MC.138457.DGemt_TB6_M12U_100_180_110_doTruthMatch_10GeVTrk.root',
      'MC.138458.DGemt_TB6_M12U_100_180_120_doTruthMatch_10GeVTrk.root',
      'MC.138459.DGemt_TB6_M12U_100_180_140_doTruthMatch_10GeVTrk.root',
      'MC.138460.DGemt_TB6_M12U_100_180_160_doTruthMatch_10GeVTrk.root',
      'MC.138461.DGemt_TB6_M12U_100_180_180_doTruthMatch_10GeVTrk.root',
      'MC.138462.DGemt_TB6_M12U_100_180_250_doTruthMatch_10GeVTrk.root',
      'MC.138463.DGemt_TB6_M12U_100_250_100_doTruthMatch_10GeVTrk.root',
      'MC.138464.DGemt_TB6_M12U_100_250_110_doTruthMatch_10GeVTrk.root',
      'MC.138465.DGemt_TB6_M12U_100_250_120_doTruthMatch_10GeVTrk.root',
      'MC.138466.DGemt_TB6_M12U_100_250_140_doTruthMatch_10GeVTrk.root',
      'MC.138467.DGemt_TB6_M12U_100_250_160_doTruthMatch_10GeVTrk.root',
      'MC.138468.DGemt_TB6_M12U_100_250_180_doTruthMatch_10GeVTrk.root',
      'MC.138469.DGemt_TB6_M12U_100_250_250_doTruthMatch_10GeVTrk.root',
      'MC.138470.DGemt_TB6_M12U_140_100_100_doTruthMatch_10GeVTrk.root',
      'MC.138471.DGemt_TB6_M12U_140_100_110_doTruthMatch_10GeVTrk.root',
      'MC.138472.DGemt_TB6_M12U_140_100_120_doTruthMatch_10GeVTrk.root',
      'MC.138473.DGemt_TB6_M12U_140_100_140_doTruthMatch_10GeVTrk.root',
      'MC.138474.DGemt_TB6_M12U_140_100_160_doTruthMatch_10GeVTrk.root',
      'MC.138475.DGemt_TB6_M12U_140_100_180_doTruthMatch_10GeVTrk.root',
      'MC.138476.DGemt_TB6_M12U_140_100_250_doTruthMatch_10GeVTrk.root',
      'MC.138477.DGemt_TB6_M12U_140_110_100_doTruthMatch_10GeVTrk.root',
      'MC.138478.DGemt_TB6_M12U_140_110_110_doTruthMatch_10GeVTrk.root',
      'MC.138479.DGemt_TB6_M12U_140_110_120_doTruthMatch_10GeVTrk.root',
      'MC.138480.DGemt_TB6_M12U_140_110_140_doTruthMatch_10GeVTrk.root',
      'MC.138481.DGemt_TB6_M12U_140_110_160_doTruthMatch_10GeVTrk.root',
      'MC.138482.DGemt_TB6_M12U_140_110_180_doTruthMatch_10GeVTrk.root',
      'MC.138483.DGemt_TB6_M12U_140_110_250_doTruthMatch_10GeVTrk.root',
      'MC.138484.DGemt_TB6_M12U_140_120_100_doTruthMatch_10GeVTrk.root',
      'MC.138485.DGemt_TB6_M12U_140_120_110_doTruthMatch_10GeVTrk.root',
      'MC.138486.DGemt_TB6_M12U_140_120_120_doTruthMatch_10GeVTrk.root',
      'MC.138487.DGemt_TB6_M12U_140_120_140_doTruthMatch_10GeVTrk.root',
      'MC.138488.DGemt_TB6_M12U_140_120_160_doTruthMatch_10GeVTrk.root',
      'MC.138489.DGemt_TB6_M12U_140_120_180_doTruthMatch_10GeVTrk.root',
      'MC.138490.DGemt_TB6_M12U_140_120_250_doTruthMatch_10GeVTrk.root',
      'MC.138491.DGemt_TB6_M12U_140_140_100_doTruthMatch_10GeVTrk.root',
      'MC.138492.DGemt_TB6_M12U_140_140_110_doTruthMatch_10GeVTrk.root',
      'MC.138493.DGemt_TB6_M12U_140_140_120_doTruthMatch_10GeVTrk.root',
      'MC.138494.DGemt_TB6_M12U_140_140_140_doTruthMatch_10GeVTrk.root',
      'MC.138495.DGemt_TB6_M12U_140_140_160_doTruthMatch_10GeVTrk.root',
      'MC.138496.DGemt_TB6_M12U_140_140_180_doTruthMatch_10GeVTrk.root',
      'MC.138497.DGemt_TB6_M12U_140_140_250_doTruthMatch_10GeVTrk.root',
      'MC.138498.DGemt_TB6_M12U_140_160_100_doTruthMatch_10GeVTrk.root',
      'MC.138499.DGemt_TB6_M12U_140_160_110_doTruthMatch_10GeVTrk.root',
      'MC.138500.DGemt_TB6_M12U_140_160_120_doTruthMatch_10GeVTrk.root',
      'MC.138501.DGemt_TB6_M12U_140_160_140_doTruthMatch_10GeVTrk.root',
      'MC.138502.DGemt_TB6_M12U_140_160_160_doTruthMatch_10GeVTrk.root',
      'MC.138503.DGemt_TB6_M12U_140_160_180_doTruthMatch_10GeVTrk.root',
      'MC.138504.DGemt_TB6_M12U_140_160_250_doTruthMatch_10GeVTrk.root',
      'MC.138505.DGemt_TB6_M12U_140_180_100_doTruthMatch_10GeVTrk.root',
      'MC.138506.DGemt_TB6_M12U_140_180_110_doTruthMatch_10GeVTrk.root',
      'MC.138507.DGemt_TB6_M12U_140_180_120_doTruthMatch_10GeVTrk.root',
      'MC.138508.DGemt_TB6_M12U_140_180_140_doTruthMatch_10GeVTrk.root',
      'MC.138509.DGemt_TB6_M12U_140_180_160_doTruthMatch_10GeVTrk.root',
      'MC.138510.DGemt_TB6_M12U_140_180_180_doTruthMatch_10GeVTrk.root',
      'MC.138511.DGemt_TB6_M12U_140_180_250_doTruthMatch_10GeVTrk.root',
      'MC.138512.DGemt_TB6_M12U_140_250_100_doTruthMatch_10GeVTrk.root',
      'MC.138513.DGemt_TB6_M12U_140_250_110_doTruthMatch_10GeVTrk.root',
      'MC.138514.DGemt_TB6_M12U_140_250_120_doTruthMatch_10GeVTrk.root',
      'MC.138515.DGemt_TB6_M12U_140_250_140_doTruthMatch_10GeVTrk.root',
      'MC.138516.DGemt_TB6_M12U_140_250_160_doTruthMatch_10GeVTrk.root',
      'MC.138517.DGemt_TB6_M12U_140_250_180_doTruthMatch_10GeVTrk.root',
      'MC.138518.DGemt_TB6_M12U_140_250_250_doTruthMatch_10GeVTrk.root',
      'MC.138519.DGemt_TB6_M12U_250_100_100_doTruthMatch_10GeVTrk.root',
      'MC.138520.DGemt_TB6_M12U_250_100_110_doTruthMatch_10GeVTrk.root',
      'MC.138521.DGemt_TB6_M12U_250_100_120_doTruthMatch_10GeVTrk.root',
      'MC.138522.DGemt_TB6_M12U_250_100_140_doTruthMatch_10GeVTrk.root',
      'MC.138523.DGemt_TB6_M12U_250_100_160_doTruthMatch_10GeVTrk.root',
      'MC.138524.DGemt_TB6_M12U_250_100_180_doTruthMatch_10GeVTrk.root',
      'MC.138525.DGemt_TB6_M12U_250_100_250_doTruthMatch_10GeVTrk.root',
      'MC.138526.DGemt_TB6_M12U_250_110_100_doTruthMatch_10GeVTrk.root',
      'MC.138527.DGemt_TB6_M12U_250_110_110_doTruthMatch_10GeVTrk.root',
      'MC.138528.DGemt_TB6_M12U_250_110_120_doTruthMatch_10GeVTrk.root',
      'MC.138529.DGemt_TB6_M12U_250_110_140_doTruthMatch_10GeVTrk.root',
      'MC.138530.DGemt_TB6_M12U_250_110_160_doTruthMatch_10GeVTrk.root',
      'MC.138531.DGemt_TB6_M12U_250_110_180_doTruthMatch_10GeVTrk.root',
      'MC.138532.DGemt_TB6_M12U_250_110_250_doTruthMatch_10GeVTrk.root',
      'MC.138533.DGemt_TB6_M12U_250_120_100_doTruthMatch_10GeVTrk.root',
      'MC.138534.DGemt_TB6_M12U_250_120_110_doTruthMatch_10GeVTrk.root',
      'MC.138535.DGemt_TB6_M12U_250_120_120_doTruthMatch_10GeVTrk.root',
      'MC.138536.DGemt_TB6_M12U_250_120_140_doTruthMatch_10GeVTrk.root',
      'MC.138537.DGemt_TB6_M12U_250_120_160_doTruthMatch_10GeVTrk.root',
      'MC.138538.DGemt_TB6_M12U_250_120_180_doTruthMatch_10GeVTrk.root',
      'MC.138539.DGemt_TB6_M12U_250_120_250_doTruthMatch_10GeVTrk.root',
      'MC.138540.DGemt_TB6_M12U_250_140_100_doTruthMatch_10GeVTrk.root',
      'MC.138541.DGemt_TB6_M12U_250_140_110_doTruthMatch_10GeVTrk.root',
      'MC.138542.DGemt_TB6_M12U_250_140_120_doTruthMatch_10GeVTrk.root',
      'MC.138543.DGemt_TB6_M12U_250_140_140_doTruthMatch_10GeVTrk.root',
      'MC.138544.DGemt_TB6_M12U_250_140_160_doTruthMatch_10GeVTrk.root',
      'MC.138545.DGemt_TB6_M12U_250_140_180_doTruthMatch_10GeVTrk.root',
      'MC.138546.DGemt_TB6_M12U_250_140_250_doTruthMatch_10GeVTrk.root',
      'MC.138547.DGemt_TB6_M12U_250_160_100_doTruthMatch_10GeVTrk.root',
      'MC.138548.DGemt_TB6_M12U_250_160_110_doTruthMatch_10GeVTrk.root',
      'MC.138549.DGemt_TB6_M12U_250_160_120_doTruthMatch_10GeVTrk.root',
      'MC.138550.DGemt_TB6_M12U_250_160_140_doTruthMatch_10GeVTrk.root',
      'MC.138551.DGemt_TB6_M12U_250_160_160_doTruthMatch_10GeVTrk.root',
      'MC.138552.DGemt_TB6_M12U_250_160_180_doTruthMatch_10GeVTrk.root',
      'MC.138553.DGemt_TB6_M12U_250_160_250_doTruthMatch_10GeVTrk.root',
      'MC.138554.DGemt_TB6_M12U_250_180_100_doTruthMatch_10GeVTrk.root',
      'MC.138555.DGemt_TB6_M12U_250_180_110_doTruthMatch_10GeVTrk.root',
      'MC.138556.DGemt_TB6_M12U_250_180_120_doTruthMatch_10GeVTrk.root',
      'MC.138557.DGemt_TB6_M12U_250_180_140_doTruthMatch_10GeVTrk.root',
      'MC.138558.DGemt_TB6_M12U_250_180_160_doTruthMatch_10GeVTrk.root',
      'MC.138559.DGemt_TB6_M12U_250_180_180_doTruthMatch_10GeVTrk.root',
      'MC.138560.DGemt_TB6_M12U_250_180_250_doTruthMatch_10GeVTrk.root',
      'MC.138561.DGemt_TB6_M12U_250_250_100_doTruthMatch_10GeVTrk.root',
      'MC.138562.DGemt_TB6_M12U_250_250_110_doTruthMatch_10GeVTrk.root',
      'MC.138563.DGemt_TB6_M12U_250_250_120_doTruthMatch_10GeVTrk.root',
      'MC.138564.DGemt_TB6_M12U_250_250_140_doTruthMatch_10GeVTrk.root',
      'MC.138565.DGemt_TB6_M12U_250_250_160_doTruthMatch_10GeVTrk.root',
      'MC.138566.DGemt_TB6_M12U_250_250_180_doTruthMatch_10GeVTrk.root',
      'MC.138567.DGemt_TB6_M12U_250_250_250_doTruthMatch_10GeVTrk.root']


MCTrueDict = {} 
MCFakeDict = {} 

for file in MC:
	MCTrueDict[file]=full_overlap(file,True)
	MCFakeDict[file]=full_overlap(file,False)

#sum_trilep=0
#sum_tau=0
#sum_track=0
#trilep_tau=0
#tau_track=0
#trilep_track=0

	
for file in MC:
	print "\\begin{frame}\n" + file + " True"
	sum_trilep = MCTrueDict[file][0]*MCTrueDict[file][6]
	sum_tau = MCTrueDict[file][1]*MCTrueDict[file][6]
	sum_track = MCTrueDict[file][2]*MCTrueDict[file][6]
	trilep_tau = MCTrueDict[file][3]*MCTrueDict[file][6]
	tau_track = MCTrueDict[file][4]*MCTrueDict[file][6]
	trilep_track = MCTrueDict[file][5]*MCTrueDict[file][6]
	print overlap_table(sum_trilep, sum_tau, sum_track, trilep_tau,  trilep_track, tau_track)

	print file + " Fake"
	sum_trilep = MCFakeDict[file][0]*MCFakeDict[file][6]
	sum_tau = MCFakeDict[file][1]*MCFakeDict[file][6]
	sum_track = MCFakeDict[file][2]*MCFakeDict[file][6]
	trilep_tau = MCFakeDict[file][3]*MCFakeDict[file][6]
	tau_track = MCFakeDict[file][4]*MCFakeDict[file][6]
	trilep_track = MCFakeDict[file][5]*MCFakeDict[file][6]
	print overlap_table(sum_trilep, sum_tau, sum_track, trilep_tau,  trilep_track, tau_track)
	print "\\end{frame}"
	
#sum_trilep=0
#sum_tau=0
#sum_track=0
#trilep_tau=0
#tau_track=0
#trilep_track=0
#
#backgrounds = [pythia_jetjet, Ttbar,SingleT,Dibosons,Zjets,Wjets,DY]
##backgrounds = [Ttbar,SingleT,Dibosons,Zjets,Wjets,DY]
#background_dict = {tuple(pythia_jetjet):"Pythia dijet", tuple(Ttbar):"TTbar",tuple(SingleT):"SingleT", tuple(Dibosons):"Dibosons", tuple(Zjets):"Zjets",tuple(Wjets):"Wjets",tuple(DY):"Drell-Yan"}
#
#for bg in backgrounds:
#	sum_trilep=0
#	sum_tau=0
#	sum_track=0
#	trilep_tau=0
#	tau_track=0
#	trilep_track=0
#	for file in bg:
#		sum_trilep+=MCTrueDict[file][0]*MCTrueDict[file][6]
#		sum_tau+=MCTrueDict[file][1]*MCTrueDict[file][6]
#		sum_track+=MCTrueDict[file][2]*MCTrueDict[file][6]
#		trilep_tau+=MCTrueDict[file][3]*MCTrueDict[file][6]
#		tau_track+=MCTrueDict[file][4]*MCTrueDict[file][6]
#		trilep_track+=MCTrueDict[file][5]*MCTrueDict[file][6]
#	print "\\begin{frame}\n" +background_dict[tuple(bg)] + " True"
#	#print sum_trilep
#	#print sum_tau
#	#print sum_track
#	#print trilep_tau
#	#print tau_track
#	#print trilep_track
#	print overlap_table(sum_trilep, sum_tau, sum_track, trilep_tau, trilep_track, tau_track)
#
#	sum_trilep=0
#	sum_tau=0
#	sum_track=0
#	trilep_tau=0
#	tau_track=0
#	trilep_track=0
#	for file in bg:
#		sum_trilep+=MCFakeDict[file][0]*MCFakeDict[file][6]
#		sum_tau+=MCFakeDict[file][1]*MCFakeDict[file][6]
#		sum_track+=MCFakeDict[file][2]*MCFakeDict[file][6]
#		trilep_tau+=MCFakeDict[file][3]*MCFakeDict[file][6]
#		tau_track+=MCFakeDict[file][4]*MCFakeDict[file][6]
#		trilep_track+=MCFakeDict[file][5]*MCFakeDict[file][6]
#	print background_dict[tuple(bg)] + " Fake"
#	#print sum_trilep
#	#print sum_tau
#	#print sum_track
#	#print trilep_tau
#	#print tau_track
#	#print trilep_track
#	print overlap_table(sum_trilep, sum_tau, sum_track, trilep_tau, trilep_track, tau_track)
#	print "\\end{frame}"
