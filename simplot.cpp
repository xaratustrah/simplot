////////////////////
// Simple plotter //
// using ROOT	  //
// 2014		  //
////////////////////


#include <TApplication.h>
#include <Riostream.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TRootCanvas.h>

//______________________________________________________________________________
// Make a histogram
TH1F * make_histo(const char* filename){

     ifstream data;
     data.open(filename);

     string tmp;
     data >> tmp; // skip the first line

     std::vector<Double_t> xvals, yvals;  
     Double_t xval, yval;

     for (data >> xval >> yval; data.good(); data >> xval >> yval){
	  xvals.push_back(xval);
	  yvals.push_back(yval);
     }

     TH1F * h = new TH1F ("h", "Plot", xvals.size(), xvals.front(), xvals.back());
     for(Int_t i=0; i < xvals.size(); ++i)
     {
	  h->SetBinContent(i+1, yvals.at(i));	  
     }
     h->SetLineColor(kRed);     
     cout << "done";
     return h;
}

//______________________________________________________________________________
int main(int argc, char ** argv) {

     if (argc != 2){
     	  cout << "Usage:\n\n";
     	  cout << "    simplot filename\n\n";
     	  exit(EXIT_SUCCESS);
     }

     TH1F * h = make_histo(argv[1]);

     TApplication app("App",&argc,argv);

     TCanvas *c = new TCanvas("c", "Plot", 1600, 700);
     c->SetGrid();
     c->ToggleEditor();
     c->ToggleEventStatus();
     c->ToggleToolBar();
     h->Draw("cl");
     c->Modified();

     c->Update(); // this line updates the canvas automatically, should come after Draw()
     // The following line to connect the close button of the window manager to the main frame, in order to close properly.
     ((TRootCanvas *)c->GetCanvasImp())->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

     app.Run();
     return 0;
}
