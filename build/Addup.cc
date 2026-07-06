void Addup() {
	TFile *verfile = new TFile("output_ver.root", "READ");
	TTree *vertree = (TTree*) verfile -> Get("tree");

	TFile *horfile = new TFile("output_hor.root", "READ");
	TTree *hortree = (TTree*) horfile -> Get("tree");

	int ver_eID;
	int vernum;
	int hor_eID;
	int hornum;
	double zpos;

	vertree -> SetBranchAddress("eid", &ver_eID);
	vertree -> SetBranchAddress("num", &vernum);
	vertree -> SetBranchAddress("zpos", &zpos);

	hortree -> SetBranchAddress("eid", &hor_eID);
	hortree -> SetBranchAddress("num", &hornum);
	
	int ver_entNum = vertree -> GetEntries();
	int hor_entNum = hortree -> GetEntries();

	unsigned long countver[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned long counthor = 0;

	double reflist[15] = {-70, -60, -50, -40, -30, -20, -10, 0, 10, 20, 30, 40, 50, 60, 70};

	for (int i = 0; i < ver_entNum; i++) {
		vertree -> GetEntry(i);

		for (int n = 0; n < 15; n++) {
			if (zpos == reflist[n]) countver[n] += vernum;
		}
	}

	for (int j = 0; j < hor_entNum; j++) {
		hortree -> GetEntry(j);
		counthor += hornum;
	}

	std::cout << "-------------------------<Analysis>-------------------------" << std::endl;
	std::cout << "Horizontal Incidence : " << counthor << std::endl;
	for (int m = 0; m < 15; m++) {
		std::cout << "Vertical Incidence at " << m << " cm : " << countver[m] << std::endl;
		std::cout << std::setprecision(4) << "H/V Ratio : " << (double) counthor/countver[m] << std::endl;
		std::cout << "------------------------------------------------------------" << std::endl;
	}
}
