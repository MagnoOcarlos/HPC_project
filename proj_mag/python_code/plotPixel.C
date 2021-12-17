{

	auto hChegada0 = new TH1D("hChegada0","Dividing the arrive spectrum by the injection spectrum.", 40, 17,21);
	auto hChegada30 = new TH1D("hChegada30","Angle 10(N=874)", 40, 17,21);
	auto hChegada90 = new TH1D("hChegada90"," Angle 50(N=175)", 40, 17,21);
	auto title = new TH1D("hChegada90"," The true injection spectrum ", 40, 17,21);


	auto hSaida0 = new TH1D("hSaida0","Angle 0", 40, 17,21);
	auto hSaida30 = new TH1D("hSaida50","Angle 10 ", 40, 17,21);
	auto hSaida90 = new TH1D("hSaida90","Angle 90", 40, 17,21);
	
	auto *f = new TF1("f","pow(x,-1)",0.1,1000);


	THStack *hs = new THStack("hs","Dividing the arrive spectrum by the injection spectrum");

	ifstream input0("injection_ang0.txt");
	ifstream input30("ang10.txt");
	ifstream input90("ang50.txt");


	//Injection Spectrum 
	int nSaida=100000;
	double E=0;

/*	for(int i=0;i<nSaida;i++){

		E=log10(f->GetRandom()*pow(10,18));
		hSaida0->Fill(E);
	}

	for(int i=0;i<nSaida;i++){

		E=log10(f->GetRandom()*pow(10,18));
		hSaida30->Fill(E);
	
	}


	for(int i=0;i<nSaida;i++){

		E=log10(f->GetRandom()*pow(10,18));
		hSaida90->Fill(E);
	}*/

	//Arrive Spectrum
	

	for(int i=0; i <=146916;i++){
		
		input0 >>E;
		E=log10(E*pow(10,18));
		hChegada0->Fill(E);
	}
/*
	for(int i=0; i <=874;i++){
		
		input30 >>E;
		E=log10(E*pow(10,18));
		hChegada30->Fill(E);
	}

	for(int i=0; i <=175;i++){
		
		input90 >>E;
		E=log10(E*pow(10,18));
		hChegada90->Fill(E);
	}*/
	//Normalization
	
	double_t factor =1.;
/*	
	hSaida0->Scale(factor/hSaida0->GetEntries());
	hSaida30->Scale(factor/hSaida0->GetEntries());
	hSaida90->Scale(factor/hSaida0->GetEntries());
	

	cout<< " " << hSaida0->GetEntries()<<"\n";
	hChegada0->Scale(factor/hChegada0->GetEntries());
	hChegada30->Scale(factor/hChegada30->GetEntries());
	hChegada90->Scale(factor/hChegada90->GetEntries());
*/
	//Ploting the injection spectrum 
	
	
	auto *c1 = new TCanvas("c1","",200,10,600,400);
	
/*	
	hChegada0->SetLineColor(kRed);
	hChegada0->SetStats(0);
	hChegada0->Draw("HIST same");	

	hChegada30->SetLineColor(kGreen);
	hChegada30->SetStats(0);
	hChegada30->Draw("HIST same");	

	hChegada90->SetLineColor(kBlue);
	hChegada90->SetStats(0);
	hChegada90->Draw("HIST same");	


	hSaida30->SetLineColor(kGreen);
	hSaida30->SetStats(0);
	hSaida30->Draw("HIST same");
	
	
	hSaida90->SetLineColor(kBlue);
	hSaida90->SetStats(0);
	hSaida90->Draw("HIST same");
*/
	c1->BuildLegend();

	//Dividing the arrive spectrum by the the injection spectrum
 
	auto *c = new TCanvas("c","ASDJ",200,10,600,400);
	TH1 * h1 = (TH1*)hChegada0->Clone("h1");
/*	TH1 * h2 = (TH1*)hChegada30->Clone("h2");
	TH1 * h3 = (TH1*)hChegada90->Clone("h3");


 	h1->Divide(hChegada0,hSaida0);	
 	h2->Divide(hChegada30,hSaida0);	
	h3->Divide(hChegada90,hSaida90);

*/
	h1->SetLineColor(kRed);
	h1->SetStats(0);
	h1->GetYaxis()->SetRangeUser(1,1e6);
	h1->GetYaxis()->SetTitle("#h_{arr}");
	h1->GetXaxis()->SetTitle("log(E)");
	h1->Draw("HIST");
/*
	h2->SetLineColor(kGreen);
	h2->SetStats(0);
	h2->Draw("HIST same");

	h3->SetLineColor(kBlue);
	h3->SetStats(0);
	h3->Draw("Hist same");
	
*/	
	auto leg = new TLegend(0.2,0.2,.8,.8);
	
	leg->AddEntry(hChegada0, "N=148488", "l");
/*	leg->AddEntry(h2, "Angle 10 (N=874)","l");
	leg->AddEntry(h3, "Angle 50 (N=175)","l");*/
	leg->Draw();

	c->SetLogy();
//	c->BuildLegend();
}
