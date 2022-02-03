#include "MyOpticalMaterialPropertiesTables.h"

#include <G4PhysicalConstants.hh>

G4MaterialPropertiesTable * MyOpticalMaterialPropertiesTables::scintillator(){
    // crystals.saint-gobain.com/radiation-detection-scintillators/plastic-scintillators/fast-timing-bc-418-bc-420-bc-422-bc-422q#
    G4MaterialPropertiesTable * mpt = new G4MaterialPropertiesTable();

    G4double energy_step = 0.05 * eV;
    G4double energy_curr = MyOpticalMaterialPropertiesTables::energy_min;
    std::vector<G4double> energies;

    do{
        energies.push_back(energy_curr);
        energy_curr += energy_step;
    }while(energy_curr < 7.5 * eV); // Put 7.5 eV instead of energy_max = 11.3 eV in order to avoid divergence.

    // Refractive index (RINDEX)
    // The refractive index is fitted to a Sellmeier function: https://en.wikipedia.org/wiki/Sellmeier_equation
    G4double A = 1.421;
    G4double B1 = 0.9944;
    G4double C1 = 26250 * pow (nm, 2);
    std::vector<G4double> rindex;

    for(auto energy: energies){
        G4double wavelength = h_Planck * c_light / energy;
        G4double rindex_element = sqrt (A + B1 * pow (wavelength, 2) / (pow (wavelength, 2) - C1));;
        rindex.push_back(rindex_element);
    }

    mpt->AddProperty("RINDEX", energies.data(), rindex.data(), energies.size());

    //Absorption length (ABSLENGTH)
    //assuming just WLS can absorb
    G4double energies_lim[]  = {MyOpticalMaterialPropertiesTables::energy_min,
                                MyOpticalMaterialPropertiesTables::energy_max};
    //from * https://www.crystals.saint-gobain.com/sites/hps-mac3-cma-crystals/files/2021-09/BC418-420-422%20Data%20Sheet.pdf
    G4double abslength[]     = {1.*m, 1.*m};
    mpt->AddProperty("ABSLENGTH", energies_lim, abslength, 2);

    //WLS absorption WLSABSLENGTH
    //assuming it is the same as for PVT
    G4double WLS_abslength[]  = {1.*m,1.*m,
                    879.673*mm ,406.487*mm ,296.786*mm,165.772*mm,
                    118.88*mm  ,96.5343*mm ,70.4532*mm,38.5933*mm,
                    26.714 *mm ,16.9549*mm ,11.2558*mm,9.49174*mm,
                    8.78259*mm ,7.31249*mm ,6.59717*mm,6.05747*mm,
                    5.24668*mm ,4.38833*mm ,3.73978*mm,2.71100*mm,
                    2.1048*mm  ,1.97013*mm ,1.20762*mm,0.71176*mm,
                    0.803417*mm,0.803417*mm,0.97114*mm,1.63289*mm};
    G4double WLS_abs_energy[] = {MyOpticalMaterialPropertiesTables::energy_min,
                    2.90388*eV,
                    2.9723 *eV,2.98595*eV,2.9987 *eV,3.00867*eV,
                    3.01317*eV,3.01997*eV,3.02443*eV,3.03555*eV,
                    3.04441*eV,3.0508*eV ,3.05709*eV,3.06822*eV,
                    3.07265*eV,3.07916*eV,3.08353*eV,3.08565*eV,
                    3.09449*eV,3.10326*eV,3.11208*eV,3.12862*eV,
                    3.14538*eV,3.15101*eV,3.20314*eV,3.25895*eV,
                    3.27264*eV,3.88859*eV,3.91598*eV,4.01202*eV};
    G4int WLS_abs_entries = 30;
    mpt->AddProperty("WLSABSLENGTH", WLS_abs_energy, WLS_abslength, WLS_abs_entries);
    
    // Emision spectrum (WLSCOMPONENT)
    // from *
    G4double WLS_emi_energy[]   = {2.3896*eV, 2.4057*eV, 2.4283*eV, 2.4514*eV, 2.4777*eV, 
            2.5118*eV, 2.5448*eV, 2.5722*eV, 2.5991*eV, 2.6231*eV, 
            2.6508*eV, 2.677*eV, 2.7058*eV, 2.7307*eV, 2.7501*eV, 
            2.7819*eV, 2.8059*eV, 2.8246*eV, 2.8457*eV, 2.86*eV, 
            2.8773*eV, 2.8933*eV, 2.908*eV, 2.9199*eV, 2.9318*eV, 
            2.9424*eV, 2.956*eV, 2.9713*eV, 2.9837*eV, 2.9946*eV, 
            3.0056*eV, 3.0199*eV, 3.0246*eV, 3.0342*eV, 3.0422*eV, 
            3.0535*eV, 3.0617*eV, 3.0732*eV, 3.083*eV, 3.0914*eV, 
            3.1064*eV, 3.1171*eV, 3.1348*eV, 3.1682*eV, 3.1953*eV, 
            3.2098*eV, 3.2208*eV, 3.2301*eV, 3.2397*eV, 3.2414*eV, 
            3.249*eV, 3.2566*eV, 3.2642*eV, 3.2681*eV, 3.274*eV, 
            3.2778*eV, 3.2836*eV, 3.2914*eV, 3.2986*eV, 3.3031*eV, 
            3.3071*eV, 3.311*eV, 3.3189*eV, 3.3268*eV, 3.3406*eV, 
            3.3485*eV, 3.3625*eV, 3.3792*eV, 3.4008*eV, 3.4211*eV, 
            3.4478*eV, 3.4866*eV, 3.5343*eV};
    G4double WLS_emi_Spectrum[] = {0.0, 0.0, 0.0, 0.0, 0.0021, 
            0.0085, 0.0128, 0.0213, 0.0233, 0.0318, 
            0.0407, 0.0519, 0.0645, 0.081, 0.0936, 
            0.1237, 0.1498, 0.1733, 0.203, 0.2258, 
            0.2539, 0.2821, 0.3081, 0.3374, 0.3609, 
            0.3917, 0.4292, 0.4727, 0.5027, 0.5307, 
            0.557, 0.6055, 0.6264, 0.6595, 0.6837, 
            0.7373, 0.76, 0.7855, 0.8163, 0.839, 
            0.8814, 0.9087, 0.9337, 0.9441, 0.9173, 
            0.8839, 0.851, 0.8169, 0.7655, 0.7277, 
            0.6862, 0.6304, 0.5892, 0.5514, 0.4858, 
            0.4614, 0.4257, 0.376, 0.3294, 0.3023, 
            0.2687, 0.2384, 0.2018, 0.1756, 0.135, 
            0.1121, 0.0865, 0.0614, 0.0382, 0.0192, 
            0.0043, 0.0, 0.0};
    G4int WLS_emi_entries = 73;
    mpt->AddProperty("WLSCOMPONENT", WLS_emi_energy, WLS_emi_Spectrum, WLS_emi_entries); 
    
    //time that the WLS takes to emmit the absorved photon
    //from *
    mpt->AddConstProperty("WLSTIMECONSTANT", 1.4 * ns);
    //mpt->AddConstProperty("WLSMEANNUMBERPHOTONS", 1);
    return mpt;
}

G4MaterialPropertiesTable * MyOpticalMaterialPropertiesTables::scintillator_2(){
    // crystals.saint-gobain.com/radiation-detection-scintillators/plastic-scintillators/fast-timing-bc-418-bc-420-bc-422-bc-422q#
    G4MaterialPropertiesTable * mpt = new G4MaterialPropertiesTable();

    G4double energy_step = 0.05 * eV;
    G4double energy_curr = MyOpticalMaterialPropertiesTables::energy_min;
    std::vector<G4double> energies;

    mpt->AddConstProperty("RINDEX", 1.31);

    //Absorption length (ABSLENGTH)
    //assuming just WLS can absorb
    G4double energies_lim[]  = {MyOpticalMaterialPropertiesTables::energy_min,
                                MyOpticalMaterialPropertiesTables::energy_max};
    //from * https://www.crystals.saint-gobain.com/sites/hps-mac3-cma-crystals/files/2021-09/BC418-420-422%20Data%20Sheet.pdf
    G4double abslength[]     = {1.*m, 1.*m};
    mpt->AddProperty("ABSLENGTH", energies_lim, abslength, 2);

    //WLS absorption WLSABSLENGTH
    //assuming it is the same as for PVT
    G4double WLS_abslength[]  = {1.*m,1.*m,
                    879.673*mm ,406.487*mm ,296.786*mm,165.772*mm,
                    118.88*mm  ,96.5343*mm ,70.4532*mm,38.5933*mm,
                    26.714 *mm ,16.9549*mm ,11.2558*mm,9.49174*mm,
                    8.78259*mm ,7.31249*mm ,6.59717*mm,6.05747*mm,
                    5.24668*mm ,4.38833*mm ,3.73978*mm,2.71100*mm,
                    2.1048*mm  ,1.97013*mm ,1.20762*mm,0.71176*mm,
                    0.803417*mm,0.803417*mm,0.97114*mm,1.63289*mm};
    G4double WLS_abs_energy[] = {MyOpticalMaterialPropertiesTables::energy_min,
                    2.90388*eV,
                    2.9723 *eV,2.98595*eV,2.9987 *eV,3.00867*eV,
                    3.01317*eV,3.01997*eV,3.02443*eV,3.03555*eV,
                    3.04441*eV,3.0508*eV ,3.05709*eV,3.06822*eV,
                    3.07265*eV,3.07916*eV,3.08353*eV,3.08565*eV,
                    3.09449*eV,3.10326*eV,3.11208*eV,3.12862*eV,
                    3.14538*eV,3.15101*eV,3.20314*eV,3.25895*eV,
                    3.27264*eV,3.88859*eV,3.91598*eV,4.01202*eV};
    G4int WLS_abs_entries = 30;
    mpt->AddProperty("WLSABSLENGTH", WLS_abs_energy, WLS_abslength, WLS_abs_entries);
    
    // Emision spectrum (WLSCOMPONENT)
    // from *
    G4double WLS_emi_energy[]   = {2.3896*eV, 2.4057*eV, 2.4283*eV, 2.4514*eV, 2.4777*eV, 
            2.5118*eV, 2.5448*eV, 2.5722*eV, 2.5991*eV, 2.6231*eV, 
            2.6508*eV, 2.677*eV, 2.7058*eV, 2.7307*eV, 2.7501*eV, 
            2.7819*eV, 2.8059*eV, 2.8246*eV, 2.8457*eV, 2.86*eV, 
            2.8773*eV, 2.8933*eV, 2.908*eV, 2.9199*eV, 2.9318*eV, 
            2.9424*eV, 2.956*eV, 2.9713*eV, 2.9837*eV, 2.9946*eV, 
            3.0056*eV, 3.0199*eV, 3.0246*eV, 3.0342*eV, 3.0422*eV, 
            3.0535*eV, 3.0617*eV, 3.0732*eV, 3.083*eV, 3.0914*eV, 
            3.1064*eV, 3.1171*eV, 3.1348*eV, 3.1682*eV, 3.1953*eV, 
            3.2098*eV, 3.2208*eV, 3.2301*eV, 3.2397*eV, 3.2414*eV, 
            3.249*eV, 3.2566*eV, 3.2642*eV, 3.2681*eV, 3.274*eV, 
            3.2778*eV, 3.2836*eV, 3.2914*eV, 3.2986*eV, 3.3031*eV, 
            3.3071*eV, 3.311*eV, 3.3189*eV, 3.3268*eV, 3.3406*eV, 
            3.3485*eV, 3.3625*eV, 3.3792*eV, 3.4008*eV, 3.4211*eV, 
            3.4478*eV, 3.4866*eV, 3.5343*eV};
    G4double WLS_emi_Spectrum[] = {0.0, 0.0, 0.0, 0.0, 0.0021, 
            0.0085, 0.0128, 0.0213, 0.0233, 0.0318, 
            0.0407, 0.0519, 0.0645, 0.081, 0.0936, 
            0.1237, 0.1498, 0.1733, 0.203, 0.2258, 
            0.2539, 0.2821, 0.3081, 0.3374, 0.3609, 
            0.3917, 0.4292, 0.4727, 0.5027, 0.5307, 
            0.557, 0.6055, 0.6264, 0.6595, 0.6837, 
            0.7373, 0.76, 0.7855, 0.8163, 0.839, 
            0.8814, 0.9087, 0.9337, 0.9441, 0.9173, 
            0.8839, 0.851, 0.8169, 0.7655, 0.7277, 
            0.6862, 0.6304, 0.5892, 0.5514, 0.4858, 
            0.4614, 0.4257, 0.376, 0.3294, 0.3023, 
            0.2687, 0.2384, 0.2018, 0.1756, 0.135, 
            0.1121, 0.0865, 0.0614, 0.0382, 0.0192, 
            0.0043, 0.0, 0.0};
    G4int WLS_emi_entries = 73;
    mpt->AddProperty("WLSCOMPONENT", WLS_emi_energy, WLS_emi_Spectrum, WLS_emi_entries); 
    
    //time that the WLS takes to emmit the absorved photon
    //from *
    mpt->AddConstProperty("WLSTIMECONSTANT", 1.4 * ns);
    //mpt->AddConstProperty("WLSMEANNUMBERPHOTONS", 1);
    return mpt;
}

G4MaterialPropertiesTable * MyOpticalMaterialPropertiesTables::liquid_argon(){
    G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();

    G4double energy_step = 0.05 * eV;
    G4double energy_curr = MyOpticalMaterialPropertiesTables::energy_min;
    std::vector<G4double> energies;

    do {
        energies.push_back(energy_curr);
        energy_curr += energy_step;
    } while(energy_curr < MyOpticalMaterialPropertiesTables::energy_max);

    // Refractive index (RINDEX)
    // https://arxiv.org/pdf/2002.09346.pdf
    G4double a0  = 0.335;
    G4double aUV = 0.099;
    G4double aIR = 0.008;
    G4double lambdaUV = 106.6 * nm;
    G4double lambdaIR = 908.3 * nm;
    std::vector<G4double> rindex;

    for(auto energy: energies){
        G4double wavelength = h_Planck * c_light / energy;
        G4double x = a0 + aUV * pow (wavelength, 2) / (pow (wavelength, 2) - pow (lambdaUV, 2)) + aIR * pow (wavelength, 2) / (pow (wavelength, 2) - pow (lambdaIR, 2));
        G4double rindex_element = sqrt (1 + 3 * x / (3 - x));
        rindex.push_back(rindex_element);
    }

    mpt->AddProperty("RINDEX", energies.data(), rindex.data(), energies.size());

    // Absorption length (ABSLENGTH)
    G4double energies_lim[]  = {MyOpticalMaterialPropertiesTables::energy_min,
                                MyOpticalMaterialPropertiesTables::energy_max};
    G4double abslength[]     = {10.*m, 10.*m};
    mpt->AddProperty("ABSLENGTH", energies_lim, abslength, 2);

    return mpt;
}

G4MaterialPropertiesTable * MyOpticalMaterialPropertiesTables::water(){
    G4MaterialPropertiesTable * mpt = new G4MaterialPropertiesTable();

    //G4double energies[] = {MyOpticalMaterialPropertiesTables::energy_min, MyOpticalMaterialPropertiesTables::energy_max};
    //G4double rindex[] = {1.33, 1.33};

    G4double energies_lim[]  = {MyOpticalMaterialPropertiesTables::energy_min,
                                MyOpticalMaterialPropertiesTables::energy_max};
    G4double abslength[]     = {10.*m, 10.*m};
    mpt->AddProperty("ABSLENGTH", energies_lim, abslength, 2);

    mpt->AddConstProperty("RINDEX", 1.33);
    return mpt;
}

