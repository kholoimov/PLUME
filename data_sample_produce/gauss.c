void gauss()
{
   TCanvas* canvas = new TCanvas("canvas", "Gaussian Distribution with Noise", 800, 600);
   TH1F* histogram = new TH1F("histogram", "Gaussian Distribution with Noise", 100, 3, 21);
   // Set the parameters of   

   TRandom3 random;
   random.SetSeed(0);// the Gaussian function

   double mean = 12.0 +random.Poisson(3);
   double stddev = 0.3 + random.Gaus(0, 0.5);
   // Create the Gaussian function
   TF1* gaussian = new TF1("gaussian", "gaus", 0, 24);
   gaussian->SetParameters(1.0, mean, stddev);
   // Generate random numbers from the Gaussian distribution and fill the histogram
   int numEntries = 10000;
   histogram->FillRandom("gaussian", numEntries);
   

   for (int i = 1; i <= histogram->GetNbinsX(); ++i) {
      double binContent = histogram->GetBinContent(i);
      double noise = random.Poisson(50); // Mean=0, StdDev=1
      std::cout << binContent << std::endl;
      if (binContent != 0) { histogram->SetBinContent(i, binContent + noise);}// Add noise to the histogram 
   }
   histogram->GetXaxis()->SetTitle("Value");
   histogram->GetYaxis()->SetTitle("Frequency");
   histogram->Draw();
   canvas->Update();

    int first_point = 7;
    int step = 2;
    int number_of_points = 8;

    int array[number_of_points];
    int histogram_sum[number_of_points];
    for (int i = 0; i < number_of_points; i++)
    {
        array[i] = first_point + step*i;
        histogram_sum[i] = histogram->Integral(histogram->GetXaxis()->FindBin(6), histogram->GetXaxis()->FindBin(array[i]));
    }

    /*
    for (int i = 0; i < number_of_points; i++)
    {
        std::cout << histogram_sum[i] << "\t";
    }
    std::cout << std::endl;
    */

   TCanvas* canvas_second = new TCanvas("canvas_second", "S_function", 800, 600);
   canvas_second->cd();
   TGraph* graph = new TGraph(number_of_points, array, histogram_sum);
   graph->SetLineWidth(5);
   graph->GetXaxis()->SetLimits(3., 21.);
   graph->GetYaxis()->SetLimits(-500, 13000);
   graph->SetMinimum(-500);
   graph->SetMaximum(13000);
   graph->Draw("AC*");
   canvas_second->Update();
   canvas_second->Draw();

   
}
