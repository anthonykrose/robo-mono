#include <vector>
#include "TGraph.h" 
#include <stdio.h>

/** @brief Makes a nice legend for DGemt
    Provide the lumi, for example "5 fb^{-1}" and the M1 as a string, i.e.
    "100". Returns a nice legend with all of the info
*/

void SetPlotStyle()
{
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;

  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);

}

void LegendDraw(string lumi, string M1){

  TLegend* legend = new TLegend(0.121, 0.62, 0.423, 0.80); 

  lumi = "#intLdt = " + lumi; 

  legend -> AddEntry((TObject*) 0x0, lumi.c_str(), ""); 
  legend -> AddEntry((TObject*) 0x0, 
		     "#frac{m_{#tilde{l}} - m_{#tilde{#chi}_{1}^{0}}}{m_{#tilde{#chi}_{1}^{#pm}} - m_{#tilde{#chi}_{1}^{0}}} = 0.5", ""); 

	legend -> SetFillColor(kWhite); 
	legend -> SetFillStyle(0);
	legend -> SetBorderSize(0);
	legend -> SetTextFont(42);
	legend -> SetTextSize(0.035);

	legend -> Draw();
}


//---------------------------------------------------------------------------------
void drawGridPlot( ){
  // MET --------------------------------

  //modeA

  draw("Simplified_model_xs", "xs_initial");

}

void draw(string filename, string cutname){


        file_name=""+filename+".root";
	const char *mycut = cutname.c_str();
	const char *mytitle = filename.c_str();
       
	drawname=filename+".eps";
	const char *mycanvas = drawname.c_str();
	SetPlotStyle();

	 
	// TH2F* h2_100 = (TH2F*) gDirectory->Get(mycut); //root file with grid points


	TH2F* GRID =new TH2F ("GRID","" , 300.,0.,300.,400,0.,400.);
	GRID->SetBinContent(85,150,4.89E-3);

	GRID->SetBinContent(107,272,1.768);
	GRID->SetBinContent(108,272,1.687);
	GRID->SetBinContent(119,272,1.636);
	GRID->SetBinContent(120,272,1.481);
	GRID->SetBinContent(107,282,1.475);
	GRID->SetBinContent(120,282,1.308);
	GRID->SetBinContent(109,293,1.394);
	GRID->SetBinContent(121,293,1.249);
	GRID->SetBinContent(100,313,1.212);
	GRID->SetBinContent(113,313,1.105);
	GRID->SetBinContent(104,323,1.064);
	GRID->SetBinContent(117,323, 0.969);
	GRID->SetBinContent(103,344,0.8735);
	GRID->SetBinContent(115,344,0.8072);
	GRID->SetBinContent(101,374,0.6496);
	GRID->SetBinContent(125,313,1.007);
	GRID->SetBinContent(125,374,0.5631);
	GRID->SetBinContent(127,344,0.7423);
	GRID->SetBinContent(129,323,0.8873);
	GRID->SetBinContent(130,272,1.515);
	GRID->SetBinContent(132,272,1.291);
	GRID->SetBinContent(132,282,1.157);
	GRID->SetBinContent(133,293,1.122);
	GRID->SetBinContent(136,313,0.9197);
	GRID->SetBinContent(139,323,0.8169);
	GRID->SetBinContent(142,272,1.117);
	GRID->SetBinContent(142,282,1.015);
	GRID->SetBinContent(146,313,0.8379);
	GRID->SetBinContent(146,374,0.4881);
	GRID->SetBinContent(148,344,0.634);
	GRID->SetBinContent(152,272,0.9362);
	GRID->SetBinContent(152,282,0.8821);
	GRID->SetBinContent(153,293,0.8952);
	GRID->SetBinContent(156,313,0.7596);
	GRID->SetBinContent(159,323,0.6837);
	GRID->SetBinContent(161,282,0.7455);
	GRID->SetBinContent(162,272,0.7508);
	GRID->SetBinContent(164,374,0.4252);
	GRID->SetBinContent(165,313,0.6918);
	GRID->SetBinContent(166,344,0.5409);
	GRID->SetBinContent(170,272,0.5491);
	GRID->SetBinContent(170,282,0.6078);
	GRID->SetBinContent(171,293,0.6789);
	GRID->SetBinContent(173,313,0.6201);
	GRID->SetBinContent(176,323,0.5686);
	GRID->SetBinContent(179,272,0.3262);
	GRID->SetBinContent(181,374,0.3705);
	GRID->SetBinContent(182,313,0.5538);
	GRID->SetBinContent(182,344,0.4606);
	GRID->SetBinContent(187,272,0.1072);
	GRID->SetBinContent(187,282,0.2975);
	GRID->SetBinContent(187,293,0.4493);
	GRID->SetBinContent(189,313,0.4836);
	GRID->SetBinContent(191,323,0.457);
	GRID->SetBinContent(194,272,0.001124);
	GRID->SetBinContent(194,282,0.1329);
	GRID->SetBinContent(197,313,0.4138);
	GRID->SetBinContent(198,344,0.3834);
	GRID->SetBinContent(202,293,0.1733);
	GRID->SetBinContent(204,313,0.3381);
	GRID->SetBinContent(206,323,0.3445);
	GRID->SetBinContent(210,374,0.2775);
	GRID->SetBinContent(211,313,0.2559);
	GRID->SetBinContent(212,344,0.3107);
	GRID->SetBinContent(216,293,0.0006208);
	GRID->SetBinContent(218,313,0.1673);
	GRID->SetBinContent(220,323,0.2201);
	GRID->SetBinContent(225,313,0.008158);
	GRID->SetBinContent(225,344,0.2355);
	GRID->SetBinContent(231,313,0.001855);
	GRID->SetBinContent(232,323,0.008403);
	GRID->SetBinContent(235,374,0.1959);
	GRID->SetBinContent(238,344,0.156);
	GRID->SetBinContent(245,323,0.0004609);
	GRID->SetBinContent(249,344,0.007402);
	GRID->SetBinContent(256,323,0.000036);
	GRID->SetBinContent(259,374,0.1136);
	GRID->SetBinContent(261,344,0.001161);
	GRID->SetBinContent(272,344,0.00006858);
	GRID->SetBinContent(280,374,0.003415);
	GRID->SetBinContent(300,374,0.00005844);
	GRID->SetBinContent(66,374,0.7325);
	GRID->SetBinContent(70,344,1.005);
	GRID->SetBinContent(76,272,2.114);
	GRID->SetBinContent(79,293,1.688);
	GRID->SetBinContent(85,313,1.324);
	GRID->SetBinContent(88,344,0.9442);
	GRID->SetBinContent(90,323,1.159);
	GRID->SetBinContent(93,272,1.906);
	GRID->SetBinContent(95,293,1.541);

	GRID->SetBinContent(102,210,2.369);
	GRID->SetBinContent(104,189,0.574);
	GRID->SetBinContent(105,231,2.329);
	GRID->SetBinContent(111,252,1.906);
	GRID->SetBinContent(116,210,1.223);
	GRID->SetBinContent(118,189,1.958e-02);
	GRID->SetBinContent(118,231,1.78);
	GRID->SetBinContent(125,252,1.601);
	GRID->SetBinContent(128,210,0.1542);
	GRID->SetBinContent(130,231,1.193);
	GRID->SetBinContent(135,252,1.293);
	GRID->SetBinContent(140,189,9.409e-07);
	GRID->SetBinContent(141,231,0.5401);
	GRID->SetBinContent(150,210,1.093e-03);
	GRID->SetBinContent(155,252,0.6162);
	GRID->SetBinContent(160,231,6.36e-03);
	GRID->SetBinContent(168,210,9.456e-10);
	GRID->SetBinContent(173,252,2.163e-02);
	GRID->SetBinContent(178,231,2.445e-05);
	GRID->SetBinContent(187,273,0.1072);
	GRID->SetBinContent(189,252,7.149e-04);
	GRID->SetBinContent(189,313,0.4836);
	GRID->SetBinContent(200,210,2.516e-10);
	GRID->SetBinContent(202,273,2.551e-03);
	GRID->SetBinContent(204,252,4.612e-07);
	GRID->SetBinContent(209,231,4.225e-10);
	GRID->SetBinContent(210,374,0.2778);
	GRID->SetBinContent(216,273,5.26e-05);
	GRID->SetBinContent(216,293,6.193e-03);
	GRID->SetBinContent(230,293,3.637e-04);
	GRID->SetBinContent(231,252,1.879e-09);
	GRID->SetBinContent(231,313,1.845e-02);
	GRID->SetBinContent(242,273,3.293e-09);
	GRID->SetBinContent(254,293,2.179e-08);
	GRID->SetBinContent(265,273,1.67e-08);
	GRID->SetBinContent(276,293,2.325e-08);
	GRID->SetBinContent(282,344,6.506e-05);
	GRID->SetBinContent(302,344,1.202e-07);
	GRID->SetBinContent(80,252,2.564);
	GRID->SetBinContent(87,210,3.383);
	GRID->SetBinContent(89,189,2.826);
	GRID->SetBinContent(90,231,2.867);
	GRID->SetBinContent(97,252,2.236);


	TGraph2D* g2_100 = new TGraph2D(GRID);  //then define a TGraph with this histo
	TGraph* g_100 = new TGraph( g2_100 ->GetN() ); 

	// if (g2_100->GetN()==0) return false;

	for(int i=0; i<g_100->GetN(); i++)
		g_100->SetPoint(i, g2_100->GetX()[i], g2_100->GetY()[i]); 
	
	g_100->SetMarkerStyle(29); 
	g_100->SetMarkerSize(1.5);

	
	g2_100->GetXaxis()->SetTitle("m_{#tilde{#tau}_{1}^{#pm}} [GeV]");   
	g2_100->GetXaxis()->SetRangeUser(0., 800.); 
	g2_100->GetYaxis()->SetTitle("m_{#tilde{#nu}} [GeV]"); 
	g2_100->GetZaxis()->SetTitle("Cross section [fb]"); 
	g2_100->GetZaxis()->CenterTitle();   
	g2_100->GetZaxis()->SetTitleOffset(1.3); 
	g2_100->GetYaxis()->SetTitleOffset(1.3); 
	g2_100->GetXaxis()->SetTitleOffset(1.3); 
	// 	g2_100->SetTitle(mytitle); 
//
	// g2_100->GetZaxis()->SetRangeUser(0.01, 10.); 


	//vector<TGraph*>  g3; 
	//vector<TGraph*> g95; 

	//double contLevels[] = {1.64};//, 3., 5.}; 
	//int Nconts = 1;

	/*TCanvas c1("dummy_3_5_95", "dummy_3_5_95"); 
	
	TH2D* h2_copy = h2_100->DrawCopy();
	TGraph2D* g2_copy = new TGraph2D(h2_copy);
	TH2D* histo = g2_copy -> GetHistogram();
	//histo -> SetContour(Nconts, contLevels); 
	//histo -> Draw("cont list"); 
	c1.Update(); 
	*/
	/*
	TObjArray *conts = (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");
	if( !conts ){
		cout<<"<AYS::GetCont_3_5_95(vector)> ERROR: Could not get list of contours." <<endl
			<<"\t Return doing nothing"<<endl;
	} else {

		TList *contLevel = 0x0; 

		contLevel = (TList*)conts->At(0);
		if( !contLevel ){
			cout<<"<AYS::GetCont_3_5_95(vector)> ERROR: Could not get 95% CL list." <<endl
				<<"\t Return doing nothing"<<endl;
		}
		for(int c=0; c<contLevel->GetSize(); c++){
			if( !contLevel->At(c) ) continue; 
			TGraph *tmp = (TGraph*) contLevel->At(c);
			tmp->SetLineWidth(4); 
			tmp->SetLineStyle(1); 
			tmp->SetLineColor(2);
			g95.push_back( tmp ); 
		}
	}
	*/
	TCanvas* sigCanvas = new TCanvas("sigCanvas", "sigCanvas", 500, 500);
	sigCanvas->SetLogz();
	sigCanvas -> SetRightMargin(0.2);
	sigCanvas -> SetLeftMargin(0.15);
	sigCanvas -> SetTopMargin(0.15);
	sigCanvas -> SetBottomMargin(0.15);
	sigCanvas ->SetGrid(0,0);


 
	gStyle -> SetPalette(1);


	g2_100 -> Draw("colz "); 




	g2_100->GetXaxis()->SetRangeUser(0., 800.); 
	gPad->Range(-100,-100,100,100);
	//for(unsigned int  c5=0;  c5 <  g5_100.size();  c5++)  g5_100.at( c5).Draw(); 
	//for(unsigned int c95=0; c95 < g95.size(); c95++) g95.at(c95)->Draw(); 
	g_100->Draw("psame"); 
// 	LegendDraw("5.8 fb^{-1}", "100"); 


	// TLatex* atlasLabel = new TLatex();
	// atlasLabel->SetNDC();
	// atlasLabel->SetTextFont(72);
	// atlasLabel->SetTextColor(ROOT::kBlack);
	// atlasLabel->SetTextSize( 0.05 );
	// // atlasLabel->DrawLatex(0.18, 0.78,"ATLAS");
	// atlasLabel->AppendPad();

	// TLatex* progressLabel = new TLatex();
	// progressLabel->SetNDC();
	// progressLabel->SetTextFont(42);
	// progressLabel->SetTextColor(ROOT::kBlack);
	// progressLabel->SetTextSize( 0.03 );
	// // progressLabel->DrawLatex(0.34, 0.78,"Preliminary");
	// progressLabel->AppendPad();
	
	TLatex *Leg1 = new TLatex();
	Leg1->SetNDC();
	Leg1->SetTextFont( 40 );
	Leg1->SetTextSize( 0.028 );
	Leg1->SetTextColor( ROOT::kBlack );
	// Leg1->DrawLatex(0.6, 0.23, "#sqrt{s}=8 TeV");
	// Leg1->DrawLatex(0.78, 0.13, "#scale[0.6]{#int} L  dt = 5.8 fb^{-1}, #sqrt{s}=8 TeV");
	Leg1->AppendPad();

	//draw kinematic line
// 	if (cutname=="Event_N_pass_nLep"){
	TLine lineExcl = TLine(150.,150.,290,290);
	lineExcl.SetLineStyle(3);
	lineExcl.SetLineWidth(3);
	lineExcl.SetLineColor(ROOT::kGray+2);
	lineExcl.Draw("same");

	TLine lineExcl2 = TLine(70.,150.3.,290,370.3);
	lineExcl2.SetLineStyle(3);
	lineExcl2.SetLineWidth(3);
	lineExcl2.SetLineColor(ROOT::kGray+2);
	lineExcl2.Draw("same");


	TLatex diagonal = TLatex(220,200,"m_{#tilde{#nu}} = m_{#tilde{#tau}_{1}}");
	diagonal.SetTextSize(0.035);
	diagonal.SetTextColor(ROOT::kGray+2);
	diagonal.SetTextAngle(45);
	diagonal.SetTextFont(42);
	diagonal.Draw("same");
	// 	}

// 	if (cutname=="Event_N_pass_2tau1lep"){
// 	  TLine lineExcl = TLine(123.,123.,605,605);
// 	  lineExcl.SetLineStyle(3);
// 	  lineExcl.SetLineWidth(3);
// 	  lineExcl.SetLineColor(ROOT::kGray+2);
// 	  lineExcl.Draw("same");
// 	  TLatex diagonal = TLatex(180,220,"m_{#tilde{#chi}^{#pm}_{1}} <m_{#tilde{#chi}^{0}_{1}}");
// 	  diagonal.SetTextSize(0.035);
// 	  diagonal.SetTextColor(ROOT::kGray+2);
// 	  diagonal.SetTextAngle(45);
// 	  diagonal.SetTextFont(42);
// 	  diagonal.Draw("same");
// 	}

// 	if (cutname=="Event_N_pass_1tau2lep"){
// 	  TLine lineExcl = TLine(123.,123.,605,605);
// 	  lineExcl.SetLineStyle(3);
// 	  lineExcl.SetLineWidth(3);
// 	  lineExcl.SetLineColor(ROOT::kGray+2);
// 	  lineExcl.Draw("same");
// 	  TLatex diagonal = TLatex(180,220,"m_{#tilde{#chi}^{#pm}_{1}} <m_{#tilde{#chi}^{0}_{1}}");
// 	  diagonal.SetTextSize(0.035);
// 	  diagonal.SetTextColor(ROOT::kGray+2);
// 	  diagonal.SetTextAngle(45);
// 	  diagonal.SetTextFont(42);
// 	  diagonal.Draw("same");
// 	}

	// g2_100->GetXaxis()->SetTitle("m_{#tilde{#chi}_{1}^{#pm}} [GeV]");   
	// g2_100->GetZaxis()->SetTitle("m_{#tilde{#chi}_{1}^{#pm}} [GeV]");   
	// g2_100->GetYaxis()->SetTitle("m_{#tilde{#chi}_{1}^{#pm}} [GeV]");   
	// g2_100 -> Draw("colz "); 

	gPad->Print("grid_plot_g2_100.eps");


	// TLatex *Leg1 = new TLatex();
	// Leg1->SetNDC();
	// Leg1->SetTextFont( 40 );
	// Leg1->SetTextSize( 0.028 );
	// Leg1->SetTextColor( ROOT::kBlack );
	// Leg1->DrawLatex(0.6, 0.08, "m_#tau");
	// Leg1->AppendPad();



	sigCanvas->Print("grid_plot.eps");
        sigCanvas->SaveAs(mycanvas);

	return;
	
}
