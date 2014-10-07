#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "TROOT.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLegend.h"
#include "THistPainter.h"
#include "TLatex.h"
#include "utils.h"

using std::string;

void writeVal(string txt, string val, double pos)
{
    TLatex* t1 = writeTLatex(txt, 0.14, pos, 0.03);
    t1->Draw();
    TLatex* t2 = writeTLatex(":", 0.23, pos, 0.03);
    t2->Draw();
    TLatex* t3 = writeTLatex(val, 0.32, pos, 0.03);
    t3->SetTextAlign(31);
    t3->Draw();
}

void plotPullTest(string filename)
{
    std::ifstream infile;
    infile.open(filename);
    // std::cout << "Reading " << filename << std::endl;
    if (!infile)
    {
	std::cout << "File empty or doesn't exist. I'm done..." << std::endl;
	return;
    }
    string title;
    std::getline(infile, title);
    // std::cout << title << std::endl;

    // Book histograms
    int nBins(20);
    double hmin(0),hmax(20);
    TH1F* h = new TH1F("h", title.c_str(), nBins, hmin, hmax);
    TH1F* h1 = new TH1F("h1", title.c_str(), nBins, hmin, hmax);
    h1->SetFillColor(2); h1->SetFillStyle(3004);
    h1->GetXaxis()->SetTitle("Pull strength (cN)");
    TH1F* h2 = new TH1F("h2", title.c_str(), nBins, hmin, hmax);
    h2->SetFillColor(4); h2->SetFillStyle(3004);
    TH1F* h3 = new TH1F("h3", title.c_str(), nBins, hmin, hmax);
    h3->SetFillColor(3); h3->SetFillStyle(3007);
    TH1F* h4 = new TH1F("h4", title.c_str(), nBins, hmin, hmax);
    h4->SetFillColor(4); h4->SetFillStyle(3005);
    TH1F* h5 = new TH1F("h5", title.c_str(), nBins, hmin, hmax);
    h5->SetFillColor(2); h5->SetFillStyle(3005);

    TCanvas *c = new TCanvas("c","Wirebond pull tests", 500, 500);

    // Loop on data
    double value, valmin, valmax;
    int type, counter(0);
    while (infile >> value >> type)
    {
	if (counter == 0) { valmax = valmin = value; }
	if (value < valmin) valmin=value;
	if (value > valmax) valmax=value;
	counter++;
	//std::cout << value << " " << type << std::endl;
	h->Fill(value);
	switch(type)
	{
	    case 1: { h1->Fill(value); break; }
	    case 2: { h2->Fill(value); break; }
	    case 3: { h3->Fill(value); break; }
	    case 4: { h4->Fill(value); break; }
	    case 5: { h5->Fill(value); break; }
	}
    }
    h->Draw();
    std::cout << "N     : " << counter << std::endl;
    std::cout << "Min   : " << valmin << std::endl;
    std::cout << "Max   : " << valmax << std::endl;
    std::cout << "Mean  : " << h->GetMean() << std::endl;
    std::cout << "Stddev: " << h->GetRMS() << std::endl;
    THStack* hs = new THStack("hs", title.c_str());
    hs->Add(h1);
    hs->Add(h2);
    hs->Add(h3);
    hs->Add(h4);
    hs->Add(h5);
    hs->Draw();
    hs->GetHistogram()->GetXaxis()->SetTitle("Pull strength (cN)");
    h->GetPainter()->PaintStat(1,0);
    TLegend *leg = new TLegend(0.1, 0.7, 0.25, 0.9);
    leg->AddEntry(h1, "Lift off 1", "f");
    leg->AddEntry(h2, "Heel break 1", "f");
    leg->AddEntry(h3, "Wire break", "f");
    leg->AddEntry(h4, "Heel break 2", "f");
    leg->AddEntry(h5, "Lift off 2", "f");
    leg->Draw();
    double pos(0.65), spacing(0.035);
    writeVal("N",toString(counter), pos);
    writeVal("Min",roundToString(valmin,2), pos-=spacing);
    writeVal("Max",roundToString(valmax,2), pos-=spacing);
    writeVal("Mean",roundToString(h->GetMean(),2), pos-=spacing);
    writeVal("Stddev",roundToString(h->GetRMS(),2), pos-=spacing);

    c->SaveAs("plotPullTest.pdf");
}

