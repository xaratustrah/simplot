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

#include "csvreader.h"

//______________________________________________________________________________
// Make a histogram
TH1F * make_histo_ssv(const char* filename){

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
// Make a histogram
TH1F * make_histo_csv(const char* filename){

     // Here is the data we want.
     data_t data;

     // Here is the file containing the data. Read it into data.
     ifstream infile( filename );
     infile >> data;

     // Complain if something went wrong.
     if (!infile.eof())
     {
	  cout << "Fooey!\n";
	  return 0;
     }

     infile.close();

     // Otherwise, list some basic information about the file.
     cout << "Your CSV file contains " << data.size() << " records.\n";

     unsigned max_record_size = 0;
     for (unsigned n = 0; n < data.size(); n++)
	  if (max_record_size < data[ n ].size())
	       max_record_size = data[ n ].size();
     cout << "The largest record has " << max_record_size << " fields.\n";

     cout << "The second field in the fourth record contains the value " << data.at(3).at(1) << ".\n";

     TH1F * h = new TH1F ("h", "Plot", data.size(), data.at(0).at(0), data.at(data.size() - 1).at(0));
     for(Int_t i=0; i < data.size(); ++i)
     {
	  h->SetBinContent(i+1, data.at(i).at(1) );	  
     }
     h->SetLineColor(kRed);     

     return h;
}

//______________________________________________________________________________
int main(int argc, char ** argv) {

     if (argc != 2){
     	  cout << "Usage:\n\n";
     	  cout << "    simplot filename\n\n";
     	  exit(EXIT_SUCCESS);
     }

     char *file_extension = argv[1] + (strlen(argv[1]) - 3); // get last 3 characters of the string, old style C programming :-)

     TH1F * h;

     if (!strcmp(file_extension, "txt"))
	  h = make_histo_ssv(argv[1]);
     else if (!strcmp(file_extension, "csv"))
	  h = make_histo_csv(argv[1]);
     else{
	  cout << "Supported file types are:\n\n" << "    space separated text with txt extension or csv files.\n\n";
	  exit(EXIT_FAILURE);
     }

     TApplication app("App",&argc,argv);

     TCanvas *c = new TCanvas("c", "Plot", 1000, 600);
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
