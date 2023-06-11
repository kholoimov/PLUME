
void multi_gauss()
{
    int number_of_s_forms = 7;
    TGraph* graphs[number_of_s_forms];
    TCanvas* canvas_second = new TCanvas("canvas_second", "S_function", 800, 600);
    for(int j = 0; j < number_of_s_forms; j++)
    {
        TH1F* histogram = new TH1F("histogram" + j, "Gaussian Distribution with Noise", 100, 3, 21);
   // Set the parameters of   

        TRandom3 random;
        random.SetSeed(0);// the Gaussian function

        double mean = 10.0 +random.Poisson(3);
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
            if (binContent != 0) { histogram->SetBinContent(i, binContent + noise);}// Add noise to the histogram 
        }
        //histogram->GetXaxis()->SetTitle("Value");
        //histogram->GetYaxis()->SetTitle("Frequency");
        //histogram->Draw();

        int first_point = 6;
        int step = 2;
        int number_of_points = 8;

        int array[number_of_points];
        int histogram_sum[number_of_points];
        for (int i = 0; i < number_of_points; i++)
        {
            array[i] = first_point + step*i;
            histogram_sum[i] = histogram->Integral(histogram->GetXaxis()->FindBin(6), histogram->GetXaxis()->FindBin(array[i])) - histogram->Integral(histogram->GetXaxis()->FindBin(6), histogram->GetXaxis()->FindBin(array[24]))*0.5;
        }

    /*
    for (int i = 0; i < number_of_points; i++)
    {
        std::cout << histogram_sum[i] << "\t";
    }
    std::cout << std::endl;
    */

        const int numColors = 9; // Number of colors in the array
        int lineColors[numColors] = {kRed, kBlue, kGreen, kMagenta, kCyan, kOrange, kViolet, kPink, kYellow};


        canvas_second->cd();
        graphs[j] = new TGraph(number_of_points, array, histogram_sum);
        graphs[j]->SetLineWidth(3);
        graphs[j]->SetLineColor(lineColors[j]);
        graphs[j]->GetXaxis()->SetLimits(3., 21.);
        graphs[j]->GetYaxis()->SetLimits(-500, 13000);
        graphs[j]->SetMinimum(-8000);
        graphs[j]->SetMaximum(8000);
        if (j == 0) {graphs[j]->Draw("APL*");}
        else {graphs[j]->Draw("LSAME*");}
        canvas_second->Update();
    }
    canvas_second->Draw();
}