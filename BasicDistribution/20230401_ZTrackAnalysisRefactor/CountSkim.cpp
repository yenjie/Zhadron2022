#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TROOT.h>
#include <TCut.h>
#include <TH1D.h>
#include <TSystem.h>

#include <iostream>
#include <fstream>
#include <iomanip>

#include "CommandLine.h"

int main(int argc, char *argv[]);

using namespace std;

TChain *TreeSig = new TChain("Tree"); 
TChain *TreeBkg = new TChain("Tree"); 
TChain *TreePP0 = new TChain("Tree"); 
//TChain *TreeSgG = new TChain("Tree"); 
//TChain *TreeBgG = new TChain("Tree"); 

TChain *TreeSigData = new TChain("Tree"); 
TChain *TreeBkgData = new TChain("Tree"); 
TChain *TreePP0Data = new TChain("Tree"); 

ofstream fout;

static double BinEdge[201] = {0, 10.5072, 11.2099, 11.8364, 12.478, 13.1194, 13.7623, 14.4081, 15.0709, 15.7532, 16.4673, 17.1881, 17.923, 18.673, 19.4865, 20.3033, 21.1536, 22.0086, 22.9046, 23.8196, 24.7924, 25.8082, 26.8714, 27.9481, 29.0828, 30.2757, 31.5043, 32.8044, 34.1572, 35.6142, 37.1211, 38.6798, 40.3116, 42.0398, 43.8572, 45.6977, 47.6312, 49.6899, 51.815, 54.028, 56.3037, 58.7091, 61.2024, 63.8353, 66.5926, 69.3617, 72.2068, 75.2459, 78.3873, 81.5916, 84.9419, 88.498, 92.1789, 95.9582, 99.8431, 103.739, 107.78, 111.97, 116.312, 120.806, 125.46, 130.269, 135.247, 140.389, 145.713, 151.212, 156.871, 162.729, 168.762, 174.998, 181.424, 188.063, 194.907, 201.942, 209.19, 216.683, 224.37, 232.291, 240.43, 248.807, 257.416, 266.256, 275.348, 284.668, 294.216, 304.053, 314.142, 324.488, 335.101, 345.974, 357.116, 368.547, 380.283, 392.29, 404.564, 417.122, 429.968, 443.116, 456.577, 470.357, 484.422, 498.78, 513.473, 528.479, 543.813, 559.445, 575.411, 591.724, 608.352, 625.344, 642.686, 660.361, 678.371, 696.749, 715.485, 734.608, 754.068, 773.846, 794.046, 814.649, 835.608, 856.972, 878.719, 900.887, 923.409, 946.374, 969.674, 993.435, 1017.62, 1042.21, 1067.28, 1092.72, 1118.64, 1144.96, 1171.71, 1198.98, 1226.67, 1254.82, 1283.46, 1312.65, 1342.21, 1372.27, 1402.85, 1433.93, 1465.49, 1497.62, 1530.29, 1563.49, 1597.22, 1631.49, 1666.37, 1701.8, 1737.75, 1774.35, 1811.51, 1849.29, 1887.75, 1926.79, 1966.6, 2006.97, 2047.99, 2089.71, 2132.1, 2175.23, 2219.17, 2263.72, 2309.2, 2355.43, 2402.47, 2450.33, 2499.05, 2548.66, 2599.16, 2650.59, 2703.03, 2756.32, 2810.75, 2866.27, 2922.91, 2980.54, 3039.47, 3099.53, 3160.98, 3223.66, 3287.71, 3353.18, 3420.34, 3489.13, 3559.72, 3632.06, 3706.18, 3782.42, 3860.78, 3941.42, 4024.52, 4110.27, 4199.4, 4292.8, 4394.49, 4519.52, 5199.95};
static double BinEdgeDown[201] = {0, 10.5071, 11.2094, 11.8357, 12.4763, 13.117, 13.7597, 14.4049, 15.0671, 15.7491, 16.4622, 17.1812, 17.9144, 18.6674, 19.4797, 20.2963, 21.1435, 21.9974, 22.8928, 23.8068, 24.7805, 25.7931, 26.8556, 27.9308, 29.0638, 30.2582, 31.4795, 32.7816, 34.1349, 35.5834, 37.0941, 38.6474, 40.2782, 42.0035, 43.8112, 45.6576, 47.5758, 49.6381, 51.6667, 53.7353, 55.8903, 58.1259, 60.4528, 62.8712, 65.3859, 67.9968, 70.7065, 73.5231, 76.4519, 79.4922, 82.6461, 85.9264, 89.3269, 92.8562, 96.5212, 100.322, 104.262, 108.344, 112.585, 116.971, 121.521, 126.225, 131.09, 136.127, 141.328, 146.721, 152.284, 158.014, 163.935, 170.054, 176.372, 182.878, 189.602, 196.532, 203.653, 211.017, 218.599, 226.387, 234.418, 242.667, 251.16, 259.886, 268.852, 278.071, 287.498, 297.2, 307.184, 317.409, 327.894, 338.66, 349.686, 360.996, 372.607, 384.508, 396.669, 409.133, 421.86, 434.906, 448.258, 461.916, 475.906, 490.16, 504.74, 519.663, 534.911, 550.453, 566.322, 582.525, 599.08, 615.968, 633.211, 650.805, 668.76, 687.048, 705.707, 724.774, 744.163, 763.9, 783.999, 804.528, 825.432, 846.746, 868.429, 890.523, 913.007, 935.952, 959.211, 982.919, 1007.08, 1031.63, 1056.62, 1082.08, 1107.96, 1134.24, 1160.99, 1188.22, 1215.91, 1244.06, 1272.69, 1301.85, 1331.45, 1361.51, 1392.07, 1423.18, 1454.77, 1486.93, 1519.57, 1552.81, 1586.55, 1620.87, 1655.79, 1691.26, 1727.27, 1763.93, 1801.12, 1838.97, 1877.47, 1916.61, 1956.45, 1996.89, 2038.04, 2079.84, 2122.35, 2165.52, 2209.53, 2254.24, 2299.83, 2346.19, 2393.31, 2441.28, 2490.16, 2539.86, 2590.57, 2642.16, 2694.74, 2748.23, 2802.81, 2858.47, 2915.33, 2973.2, 3032.28, 3092.56, 3154.24, 3217.19, 3281.45, 3347.18, 3414.6, 3483.65, 3554.56, 3627.2, 3701.66, 3778.25, 3856.97, 3937.98, 4021.48, 4107.62, 4197.21, 4291.05, 4393.19, 4518.6, 5199.95};
static double BinEdgeUp[201] = {0, 10.5075, 11.2107, 11.838, 12.4797, 13.1213, 13.7641, 14.4124, 15.0745, 15.7577, 16.473, 17.1939, 17.9297, 18.6812, 19.4958, 20.3143, 21.1648, 22.0218, 22.9159, 23.8328, 24.8059, 25.8204, 26.89, 27.9702, 29.1042, 30.3022, 31.528, 32.8347, 34.1896, 35.6439, 37.1542, 38.7172, 40.3518, 42.091, 43.9053, 45.7415, 47.6853, 49.7457, 51.8755, 54.0983, 56.3594, 58.7848, 61.2861, 63.9228, 66.6825, 69.4421, 72.297, 75.3547, 78.4967, 81.6977, 85.0755, 88.6211, 92.3058, 96.1071, 99.9975, 104.065, 108.272, 112.512, 116.906, 121.601, 126.465, 131.482, 136.866, 142.229, 147.786, 153.546, 159.571, 165.586, 171.902, 178.419, 185.063, 191.856, 199.055, 206.261, 213.999, 221.719, 229.671, 237.84, 246.088, 254.828, 263.883, 272.907, 282.236, 291.925, 301.519, 311.477, 321.691, 332.153, 342.892, 353.878, 365.161, 376.742, 388.577, 400.684, 413.075, 425.746, 438.711, 451.989, 465.556, 479.45, 493.608, 508.077, 522.891, 538.003, 553.415, 569.151, 585.216, 601.601, 618.354, 635.422, 652.84, 670.599, 688.699, 707.161, 726.014, 745.185, 764.687, 784.557, 804.838, 825.489, 846.537, 867.951, 889.752, 911.955, 934.588, 957.52, 980.912, 1004.73, 1028.94, 1053.57, 1078.67, 1104.17, 1130.07, 1156.39, 1183.2, 1210.47, 1238.17, 1266.38, 1295.02, 1324.16, 1353.71, 1383.77, 1414.35, 1445.41, 1477, 1509.09, 1541.74, 1574.88, 1608.59, 1642.83, 1677.66, 1713.07, 1748.98, 1785.47, 1822.63, 1860.33, 1898.72, 1937.73, 1977.42, 2017.71, 2058.62, 2100.25, 2142.57, 2185.56, 2229.38, 2273.91, 2319.2, 2365.33, 2412.22, 2459.94, 2508.52, 2557.98, 2608.35, 2659.61, 2711.86, 2765, 2819.23, 2874.58, 2930.97, 2988.46, 3047.12, 3106.95, 3168.15, 3230.6, 3294.37, 3359.58, 3426.47, 3494.95, 3565.21, 3637.21, 3711.03, 3786.91, 3864.85, 3945.11, 4027.8, 4113.06, 4201.73, 4294.72, 4395.9, 4520.5, 5199.95};
   

void CountSkim_single(CommandLine &CL,float ptL=20,float ptH=2000,int centL=0,int centH=90,float TptL=0,float TptH=10000/*,double t0[8]={0},double z0[8]={0}*/){

	int CentUD = CL.GetInteger("CentUD", 0);
	string OutputFileName = CL.Get("Output", "SkimCount30.txt");

	double HFShift        = CL.GetDouble("HFShift",682);
	double HFShiftData    = CL.GetDouble("HFShiftData",660);
    double HFTolerance    = CL.GetDouble("Tolerance",187.5);
    double HFToleranceData= CL.GetDouble("ToleranceData",150);
    //HFToleranceFraction   = CL.GetDouble("ToleranceFraction");

    int ZWtID= CL.GetInteger("ZWtID",-1);
    double VZMin= CL.GetDouble("VZMin",-10000);
    double VZMax= CL.GetDouble("VZMax",10000);

    int ppNPU= CL.GetInteger("ppNPU",0);

    fout<<"HFShift = "<<HFShift<<", HFTolerance = "<<HFTolerance<<endl;
    fout<<"ptL = "<<ptL<<", ptH = "<<ptH<<", centL = "<<centL<<", centH = "<<centH<<", TptL = "<<TptL<<", TptH = "<<TptH<<std::endl;

   	double cent[201];

   	for(int i=0;i<201;i++){
   		if(CentUD==0)
   			cent[i]=BinEdge[i];
   		else if(CentUD==1)
   			cent[i]=BinEdgeUp[i];
   		else if(CentUD==2)
   			cent[i]=BinEdgeDown[i];
   		else
   			cent[i]=0;
   	}

	TCut evtCut = Form("zMass[0]>60&&zPt[0]>%f&&zPt[0]<%f&&hiHF<=%f&&hiHF>%f",ptL,ptH,cent[200-2*centL],cent[200-2*centH]);
	TCut evtCutGen = Form("genZMass[0]>60&&genZPt[0]>%f&&genZPt[0]<%f&&hiHF<=%f&&hiHF>%f",ptL,ptH,cent[200-2*centL],cent[200-2*centH]);
	TCut trkCut = Form("trackMuTagged==0&&trackPt>%f&&trackPt<%f",TptL,TptH);
	TCut evtCutPP = Form("zMass[0]>60&&zPt[0]>%f&&zPt[0]<%f",ptL,ptH);

	TCut VZCut = Form("SignalVZ>%f&&SignalVZ<%f",VZMin,VZMax);
	//string ZWt = Form("NCollWeight*ZWeight*ExtraZWeight[%d]*VZWeight",ZWtID);

	string ExtZwt = "ExtraZWeight["+ Form("%d",ZWtID) + "]";
	if(ZWtID==-1) 
		ExtZwt = "";

	//string TrkWt = "(" + ZWt + "*trackWeight*trackResidualWeight)";
	TCut ppNPUcut = "";
	if(ppNPU==0)
		ppNPUcut = (TCut) "NPU==0";

	TCut SBHF = "";//Form("SignalHF-BackgroundHF>%f&&SignalHF-BackgroundHF<%f",HFShift-HFTolerance,HFShift+HFTolerance);
	TCut SBHFData = "";//Form("SignalHF-BackgroundHF>%f&&SignalHF-BackgroundHF<%f",HFShiftData-HFToleranceData,HFShiftData+HFToleranceData);

	TH1D HNSig("HNSig","Normalization", 1, 0, 1);
	TH1D HNBkg("HNBkg","Normalization", 1, 0, 1);
	//TH1D HNSgG("HNSgG","Normalization", 1, 0, 1);
	TH1D HNPP0("HNPP0","Normalization", 1, 0, 1);
	//TH1D HNBgG("HNBgG","Normalization", 1, 0, 1);
	TH1D HNSigData("HNSigData","Normalization", 1, 0, 1);
	TH1D HNBkgData("HNBkgData","Normalization", 1, 0, 1);
	TH1D HNPP0Data("HNPP0Data","Normalization", 1, 0, 1);

	if(ZWtID==-1)
	TreeSig		 ->Draw("0>>HNSig",Form("(NCollWeight*ZWeight*%s*VZWeight*trackWeight*trackResidualWeight)",ExtZwt)*(VZCut&&evtCut&&trkCut));
	TreeBkg		 ->Draw("0>>HNBkg",Form("(NCollWeight*ZWeight*%s*VZWeight*trackWeight*trackResidualWeight)",ExtZwt)*(VZCut&&evtCut&&trkCut&&SBHF));
	//TreeSgG		 ->Draw("0>>HNSgG",Form("(NCollWeight*ZWeight*%s*VZWeight*trackWeight*trackResidualWeight)",ExtZwt)*(VZCut&&evtCutGen&&trkCut));
	TreePP0		 ->Draw("0>>HNPP0",Form("(NCollWeight*ZWeight*%s*VZWeight*trackWeight*trackResidualWeight)",ExtZwt)*(VZCut&&evtCutPP&&trkCut&&ppNPU));
	//TreeBgG		 ->Draw("0>>HNBgG",Form("(NCollWeight*ZWeight*%s*VZWeight*trackWeight*trackResidualWeight)",ExtZwt)*(VZCut&&evtCutGen&&trkCut&&SBHF));
	TreeSigData->Draw("0>>HNSigData",Form("(NCollWeight*ZWeight*%s*VZWeight*trackWeight*trackResidualWeight)",ExtZwt)*(VZCut&&evtCut&&trkCut));
	TreeBkgData->Draw("0>>HNBkgData",Form("(NCollWeight*ZWeight*%s*VZWeight*trackWeight*trackResidualWeight)",ExtZwt)*(VZCut&&evtCut&&trkCut&&SBHFData));
	TreePP0Data->Draw("0>>HNPP0Data",Form("(NCollWeight*ZWeight*%s*VZWeight*trackWeight*trackResidualWeight)",ExtZwt)*(VZCut&&evtCutPP&&trkCut));

	double t1N = HNSig.GetBinContent(1);
	double t2N = HNBkg.GetBinContent(1);
	//double t3N = HNSgG.GetBinContent(1);
	double t4N = HNPP0.GetBinContent(1);
	//double t5N = HNBgG.GetBinContent(1);
	double t6N = HNSigData.GetBinContent(1);
	double t7N = HNBkgData.GetBinContent(1);
	double t8N = HNPP0Data.GetBinContent(1);

	double t1E = HNSig.GetBinError(1);
	double t2E = HNBkg.GetBinError(1);
	//double t3E = HNSgG.GetBinError(1);
	double t4E = HNPP0.GetBinError(1);
	//double t5E = HNBgG.GetBinError(1);
	double t6E = HNSigData.GetBinError(1);
	double t7E = HNBkgData.GetBinError(1);
	double t8E = HNPP0Data.GetBinError(1);


	TH1D HNSig1("HNSig1","Normalization", 1, 0, 1);
	TH1D HNBkg1("HNBkg1","Normalization", 1, 0, 1);
	//TH1D HNSgG1("HNSgG1","Normalization", 1, 0, 1);
	TH1D HNPP01("HNPP01","Normalization", 1, 0, 1);
	//TH1D HNBgG1("HNBgG1","Normalization", 1, 0, 1);
	TH1D HNSigData1("HNSigData1","Normalization", 1, 0, 1);
	TH1D HNBkgData1("HNBkgData1","Normalization", 1, 0, 1);
	TH1D HNPP0Data1("HNPP0Data1","Normalization", 1, 0, 1);

	TreeSig		 ->Draw("0>>HNSig1",Form("(NCollWeight*ZWeight*%s*VZWeight)",ExtZwt)*(VZCut&&evtCut));
	TreeBkg		 ->Draw("0>>HNBkg1",Form("(NCollWeight*ZWeight*%s*VZWeight)",ExtZwt)*(VZCut&&evtCut&&SBHF));
	//TreeSgG		 ->Draw("0>>HNSgG1",Form("(NCollWeight*ZWeight*%s*VZWeight)",ExtZwt)*(VZCut&&evtCutGen));
	TreePP0		 ->Draw("0>>HNPP01",Form("(NCollWeight*ZWeight*%s*VZWeight)",ExtZwt)*(VZCut&&evtCutPP&&ppNPU));
	//TreeBgG		 ->Draw("0>>HNBgG1",Form("(NCollWeight*ZWeight*%s*VZWeight)",ExtZwt)*evtCutGen);
	TreeSigData->Draw("0>>HNSigData1",Form("(NCollWeight*ZWeight*%s*VZWeight)",ExtZwt)*(VZCut&&evtCut));
	TreeBkgData->Draw("0>>HNBkgData1",Form("(NCollWeight*ZWeight*%s*VZWeight)",ExtZwt)*(VZCut&&evtCut&&SBHFData));
	TreePP0Data->Draw("0>>HNPP0Data1",Form("(NCollWeight*ZWeight*%s*VZWeight)",ExtZwt)*(VZCut&&evtCutPP));

	double z1N = HNSig1.GetBinContent(1);
	double z2N = HNBkg1.GetBinContent(1);
	//double z3N = HNSgG1.GetBinContent(1);
	double z4N = HNPP01.GetBinContent(1);
	//double z5N = HNBgG1.GetBinContent(1);
	double z6N = HNSigData1.GetBinContent(1);
	double z7N = HNBkgData1.GetBinContent(1);
	double z8N = HNPP0Data1.GetBinContent(1);

	int z1N0 = HNSig1.GetEntries();
	int z2N0 = HNBkg1.GetEntries();
	//int z3N0 = HNSgG1.GetEntries();
	int z4N0 = HNPP01.GetEntries();
	//int z5N0 = HNBgG1.GetEntries();
	int z6N0 = HNSigData1.GetEntries();
	int z7N0 = HNBkgData1.GetEntries();
	int z8N0 = HNPP0Data1.GetEntries();

	double z1E = HNSig1.GetBinError(1);
	double z2E = HNBkg1.GetBinError(1);
	//double z3E = HNSgG1.GetBinError(1);
	double z4E = HNPP01.GetBinError(1);
	//double z5E = HNBgG1.GetBinError(1);
	double z6E = HNSigData1.GetBinError(1);
	double z7E = HNBkgData1.GetBinError(1);
	double z8E = HNPP0Data1.GetBinError(1);

	double et1 = t1E/t1N, et2 = t2E/t2N, et4 = t4E/t4N, et6 = t6E/t6N, et7 = t7E/t7N, et8 = t8E/t8N;
	double ez1 = z1E/z1N, ez2 = z2E/z2N, ez4 = z4E/z4N, ez6 = z6E/z6N, ez7 = z7E/z7N, ez8 = z8E/z8N;

	fout<<"======================================"<<std::endl;

	fout<<left<<setw(15)<< "Sample"           <<setw(2)<<"|"<<left<<setw(15)<< "PbPb Sig MC" <<setw(2)<<"|"<<left<<setw(15)<< "PbPb Bkg MC" <<setw(2)<<"|"<<left<<setw(15)<< "PbPb Sig-Bkg MC" <<setw(2)<<"|"<<left<<setw(15)<< "ppMC NPU=0" <<endl;
	fout<<left<<setw(15)<< "N_Z (unweighted)" <<setw(2)<<"|"<<left<<setw(15)<< z1N0          <<setw(2)<<"|"<<left<<setw(15)<< z2N0          <<setw(2)<<"|"<<left<<setw(15)<< z1N0-z2N0         <<setw(2)<<"|"<<left<<setw(15)<< z4N0         <<endl;
	fout<<left<<setw(15)<< "Nevt (weighted)"  <<setw(2)<<"|"<<left<<setw(15)<< z1N           <<setw(2)<<"|"<<left<<setw(15)<< z2N           <<setw(2)<<"|"<<left<<setw(15)<< z1N-z2N           <<setw(2)<<"|"<<left<<setw(15)<< z4N          <<endl;
	fout<<left<<setw(15)<< "Ntrk/Nevt" 	      <<setw(2)<<"|"<<left<<setw(15)<< t1N/z1N       <<setw(2)<<"|"<<left<<setw(15)<< t2N/z2N       <<setw(2)<<"|"<<left<<setw(15)<< t1N/z1N-t2N/z2N   <<setw(2)<<"|"<<left<<setw(15)<< t4N/z4N      <<endl;
	fout<<left<<setw(15)<< "Error"     	      <<setw(2)<<"|"<<left<<setw(15)<< t1E/z1N       <<setw(2)<<"|"<<left<<setw(15)<< t2E/z2N       <<setw(2)<<"|"<<left<<setw(15)<< sqrt((t1E/z1N)*(t1E/z1N)+(t2E/z2N)*(t2E/z2N)) <<setw(2)<<"|"<<left<<setw(15)<< t4E/z4N      <<endl;

	fout<<"--------------------------------------"<<std::endl;

	fout<<left<<setw(15)<< "Sample"           <<setw(2)<<"|"<<left<<setw(15)<< "PbPb Sig Data"<<setw(2)<<"|"<<left<<setw(15)<< "PbPb Bkg Data"<<setw(2)<<"|"<<left<<setw(15)<< "PbPb Sig-Bkg Data"<<setw(2)<<"|"<<left<<setw(15)<< "pp Data NPU=0" <<endl;
	fout<<left<<setw(15)<< "N_Z (unweighted)" <<setw(2)<<"|"<<left<<setw(15)<< z6N0           <<setw(2)<<"|"<<left<<setw(15)<< z7N0           <<setw(2)<<"|"<<left<<setw(15)<< z6N0-z7N0          <<setw(2)<<"|"<<left<<setw(15)<< z8N0            <<endl;
	fout<<left<<setw(15)<< "Nevt (weighted)"  <<setw(2)<<"|"<<left<<setw(15)<< z6N            <<setw(2)<<"|"<<left<<setw(15)<< z7N            <<setw(2)<<"|"<<left<<setw(15)<< z6N-z7N            <<setw(2)<<"|"<<left<<setw(15)<< z8N             <<endl;
	fout<<left<<setw(15)<< "Ntrk/Nevt" 	      <<setw(2)<<"|"<<left<<setw(15)<< t6N/z6N        <<setw(2)<<"|"<<left<<setw(15)<< t7N/z7N        <<setw(2)<<"|"<<left<<setw(15)<< t6N/z6N-t7N/z7N    <<setw(2)<<"|"<<left<<setw(15)<< t8N/z8N         <<endl;
	fout<<left<<setw(15)<< "Error"     	      <<setw(2)<<"|"<<left<<setw(15)<< t6E/z6N        <<setw(2)<<"|"<<left<<setw(15)<< t7E/z7N        <<setw(2)<<"|"<<left<<setw(15)<< sqrt((t6E/z6N)*(t6E/z6N)+(t7E/z7N)*(t7E/z7N)) <<setw(2)<<"|"<<left<<setw(15)<< t8E/z8N      <<endl;

	fout<<"======================================"<<std::endl;

	string OutputFileNameBkup = OutputFileName;
	OutputFileNameBkup.replace(OutputFileNameBkup.end()-4,OutputFileNameBkup.end(),"_bkup.txt");

	gSystem->Exec(("cp " + OutputFileName + " " + OutputFileNameBkup).c_str());

}
//void CountSkim(){
int main(int argc, char *argv[]){

	CommandLine CL(argc, argv);

	string InputBase      = CL.Get("InputBase", "/eos/cms/store/group/phys_heavyions/pchou/");
   	string OutputFileName = CL.Get("Output", "SkimCount30.txt");
   	string BkgDataDir     = CL.Get("BkgDataDir", "OutputDataBackground_v15b");
   	string BkgMCDir		  = CL.Get("BkgMCDir", "OutputMCBackground_v15b");
   	//string BkgMCGenDir	  = CL.Get("BkgMCGenDir", "OutputMCbkgGen_v14");

   	string SigMCDir		  = CL.Get("SigMCDir", "OutputMC_v15");
   	string SigPPMCDir     = CL.Get("SigPPMCDir", "OutputPPMC_v15");
   	string SigPPDataDir	  = CL.Get("SigPPDataDir", "OutputPPData_v15");
   	string SigDataDir	  = CL.Get("SigDataDir", "OutputData_v15");

   	//int CentUD = CL.Get("CentUD", 0);
   	//int UEUD = CL.Get("UEUD", 0);

	fout.open(OutputFileName);

	string YiBase = "/eos/cms/store/group/phys_heavyions/chenyi/PhysicsWorkspace/HIZHadron2022/Skims/20230310_ZHadronSkims/";

	TreeSig->Add((YiBase + SigMCDir + "/Result1*.root?#Tree").c_str());
	TreePP0->Add((YiBase + SigPPMCDir + "/Result*.root?#Tree").c_str());
	TreeBkg->Add((InputBase + BkgMCDir + "/Result1*.root?#Tree").c_str());
	TreeSigData->Add((YiBase + SigDataDir + "/Result5*.root?#Tree").c_str());
	TreeSigData->Add((YiBase + SigDataDir + "/Result6*.root?#Tree").c_str());
	TreeBkgData->Add((InputBase + BkgDataDir + "/Result5*.root?#Tree").c_str());
	TreeBkgData->Add((InputBase + BkgDataDir + "/Result6*.root?#Tree").c_str());
	TreePP0Data->Add((YiBase + SigPPDataDir + "/Result5*.root?#Tree").c_str());
	TreePP0Data->Add((YiBase + SigPPDataDir + "/Result6*.root?#Tree").c_str());

	CountSkim_single(CL,40,200,0,30,1,2);
	CountSkim_single(CL,40,200,0,30,2,4);
	CountSkim_single(CL,40,200,0,30,4,10);
	CountSkim_single(CL,40,200,0,30,10,20);
	CountSkim_single(CL,40,200,0,30,20,50);
	CountSkim_single(CL,40,200,30,50,1,2);
	CountSkim_single(CL,40,200,30,50,2,4);
	CountSkim_single(CL,40,200,30,50,4,10);
	CountSkim_single(CL,40,200,30,50,10,20);
	CountSkim_single(CL,40,200,30,50,20,50);
	CountSkim_single(CL,40,200,50,90,1,2);
	CountSkim_single(CL,40,200,50,90,2,4);
	CountSkim_single(CL,40,200,50,90,4,10);
	CountSkim_single(CL,40,200,50,90,10,20);
	CountSkim_single(CL,40,200,50,90,20,50);

	CountSkim_single(CL,20,2000,0,10,10,20);
	CountSkim_single(CL,20,2000,0,10,20,50);
	CountSkim_single(CL,20,2000,0,10,50,100);
	CountSkim_single(CL,20,2000,0,90,10,20);
	CountSkim_single(CL,20,2000,0,90,20,50);
	CountSkim_single(CL,20,2000,0,90,50,100);

	fout.close();

	return 0;
}
