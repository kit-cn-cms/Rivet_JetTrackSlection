// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Tools/Logging.hh"
#include "Rivet/Tools/ParticleIdUtils.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/ChargedFinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/ChargedLeptons.hh"

namespace Rivet {


  class BTAG_JET_TRACK_SEL_OLD : public Analysis {
  public:

    /// Constructor
    BTAG_JET_TRACK_SEL_OLD()
      : Analysis("BTAG_JET_TRACK_SEL_OLD")
    {
      setNeedsCrossSection(false);
      
      njetflavors     = 4;
      
      jetflavor[0]    = -1;
      jetflavor[1]    = 0;
      jetflavor[2]    = 4;
      jetflavor[3]    = 5;
      
      jetflavorname[0] = "All";
      jetflavorname[1] = "Light";
      jetflavorname[2] = "Charm";
      jetflavorname[3] = "Bottom";
    }


  public:

    /// @name Analysis methods
    //@{

    /// Book histograms and initialise projections before the run
    void init() {
      
      const FinalState fs(-2.5,2.5);
      const ChargedFinalState cfs(-2.5,2.5);
      addProjection(fs, "FS");
      addProjection(cfs, "CFS");
      addProjection(FastJets(fs, FastJets::ANTIKT, 0.5), "Jets");
      addProjection(ChargedLeptons(fs), "Leptons");
      
      for(int jetflav=0;jetflav<njetflavors;jetflav++){
        _h_JetFlavor[jetflav]                   = bookHisto1D("A_JetFlavor_"+jetflavorname[jetflav]+"Jets", 7, -1.5, 5.5);
        _h_NParticles[jetflav]                  = bookHisto1D("B_NParticles_"+jetflavorname[jetflav]+"Jets", 50, 0., 100.);
        _h_NChargedParticles[jetflav]           = bookHisto1D("C_NChargedParticles_"+jetflavorname[jetflav]+"Jets", 50, 0., 50.);

        _h_ChargedParticlePt[jetflav]           = bookHisto1D("D_ChargedParticlePt_"+jetflavorname[jetflav]+"Jets", 60, 0., 120.);
        _h_ChargedParticlePtUncut[jetflav]      = bookHisto1D("E_ChargedParticlePtUncut_"+jetflavorname[jetflav]+"Jets", 20, 0., 10.);
        _h_ChargedParticlePtRel[jetflav]        = bookHisto1D("F_ChargedParticlePtRel_"+jetflavorname[jetflav]+"Jets", 70, 0., .07);
        _h_ChargedParticleJetDist[jetflav]      = bookHisto1D("G_ChargedParticleJetDist_"+jetflavorname[jetflav]+"Jets", 50, 0., 1.);
        _h_ChargedParticleJetDr[jetflav]        = bookHisto1D("H_ChargedParticleJetDr_"+jetflavorname[jetflav]+"Jets", 70, 0., .7);
        _h_ChargedParticlePVD[jetflav]          = bookHisto1D("I_ChargedParticlePVD_"+jetflavorname[jetflav]+"Jets", 50, 0., 10.);
        _h_ChargedParticlePVDxy[jetflav]        = bookHisto1D("J_ChargedParticlePVDxy_"+jetflavorname[jetflav]+"Jets", 60, 0., 3.);
        _h_ChargedParticlePVDz[jetflav]         = bookHisto1D("K_ChargedParticlePVDz_"+jetflavorname[jetflav]+"Jets", 50, 0., 10.);
        _h_ChargedParticlePCAPVD[jetflav]       = bookHisto1D("L_ChargedParticlePCAPVD_"+jetflavorname[jetflav]+"Jets", 50, 0., 100.);
        _h_ChargedParticleIP[jetflav]           = bookHisto1D("M_ChargedParticleIP_"+jetflavorname[jetflav]+"Jets", 50, -3., 7.);
        
        _h_ChargedTrackVertexPVDist[jetflav]    = bookHisto1D("N_ChargedTrackVertexPVDist_"+jetflavorname[jetflav]+"Jets", 50, 0., 150.);
        _h_NChargedParticlesSecVertex[jetflav]  = bookHisto1D("O_NChargedParticlesSecVertex_"+jetflavorname[jetflav]+"Jets", 30, 0., 30.);
        _h_NSecVertex[jetflav]                  = bookHisto1D("P_NSecVertex_"+jetflavorname[jetflav]+"Jets", 11, -.5, 10.5);
        _h_SecVertexMass[jetflav]               = bookHisto1D("Q_SecVertexMass_"+jetflavorname[jetflav]+"Jets", 50, 0., 10.);
        _h_SecVertexJetDr[jetflav]              = bookHisto1D("R_SecVertexJetDr_"+jetflavorname[jetflav]+"Jets", 40, 0., 4.);
        
        _h_MuonPtRel[jetflav]                   = bookHisto1D("S_MuonPtRel_"+jetflavorname[jetflav]+"Jets", 40, 0., 20.);
        _h_MuonJetDr[jetflav]                   = bookHisto1D("T_MuonJetDr_"+jetflavorname[jetflav]+"Jets", 70, 0., .7);     
      }
    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {
      //Get Event Weight
      const float weight = event.weight();
      
      //Get final state particles
      Particles particles = applyProjection<FinalState>(event,"FS").particles();
      
      //Get charged final state particles
      Particles cparticles = applyProjection<ChargedFinalState>(event,"CFS").particles();

      //Get Primary Vertex
      ThreeVector pvertex = PVertexFinder(particles, pvertexcutoff);

      //Get ak5 Jets
      const Jets jets = applyProjection<FastJets>(event, "Jets").jetsByPt(pt_min_jets);
      
      //Initialize Loop Variables
      int njet = 0;
      
      //Loop over all Jets
      foreach (const Jet& j, jets) {
        
        //Get Jet Momentum Vector
        const FourMomentum fourmomentum_jet = j.momentum();
        const ThreeVector threemomentum_jet(fourmomentum_jet.x(),fourmomentum_jet.y(),fourmomentum_jet.z());
        
        //Get Jet Flavor
        int jetflavorID = -1;
        if(j.containsBottom()) jetflavorID = 3;
        else if(j.containsCharm()) jetflavorID = 2;
        else jetflavorID = 1;
        
	      //Apply Kinematic Jet Cuts
        if(j.momentum().pT()<pt_min_jets) continue;
        if(fabs(j.eta())>eta_max_jets) continue;

        //Count Selected Jets
        njet++;
        
        //Fill Jet Histograms
        _h_JetFlavor[0]->fill(jetflavor[jetflavorID], weight);
        _h_JetFlavor[jetflavorID]->fill(jetflavor[jetflavorID], weight);
        _h_NParticles[0]->fill(j.size(), weight);
        _h_NParticles[jetflavorID]->fill(j.size(), weight);

        //Initialize Loop Variables for Charged Particles
        int ncparticles = 0;
        int ncpsecvtx = 0;
	      Particles selcparticles;

        foreach (const Particle& cp, cparticles){

          //Apply Charged Particle Kinematics Selection
          //if(cp.momentum().pT()<pt_min_cp) continue;
          if(fabs(cp.momentum().eta())>eta_max_cp) continue;

          //Calculate Charged Particle Jet Delta R
          float dr_jet_cp = deltaR(j.momentum(), cp.momentum());

          //Apply Jet Charged Particle Delta R Selection
          if(dr_jet_cp>dr_jet_cp_max) continue;

          //Get Charged Particle Production Vertex
          HepMC::FourVector particlevertex = cp.genParticle()->production_vertex()->position();
          const ThreeVector particlevertex3d(particlevertex.x(),particlevertex.y(),particlevertex.z());

          //Get Charged Particle Momentum Vector
          const FourMomentum fourmomentum_cp = cp.momentum();
          const ThreeVector threemomentum_cp(fourmomentum_cp.x(),fourmomentum_cp.y(),fourmomentum_cp.z());

          //Calculate Cross Vector for Jet & Charged Particle
          ThreeVector threevec_jet_cross_cp = cross(threemomentum_jet,threemomentum_cp);
	        if(threevec_jet_cross_cp.mod()!=0)threevec_jet_cross_cp /= threevec_jet_cross_cp.mod();

          //Calculate Distance of Closest Approach between Jet and Charged Particle
          float d_jet_cp = fabs(dot((particlevertex3d-pvertex),threevec_jet_cross_cp));

          //Apply Jet Charged Particle Distance Selection
          if(d_jet_cp>d_jet_cp_max) continue;

          //Calculate Distance of Closest Approach between Primary Vertex and Charged Particle
	        const ThreeVector threemomentum_norm_cp = threemomentum_cp/threemomentum_cp.mod();
          const ThreeVector threevec_d_pv_cp = dot((pvertex-particlevertex3d),threemomentum_norm_cp) * threemomentum_norm_cp - (pvertex-particlevertex3d);
          float d_pv_cp = threevec_d_pv_cp.mod();
          float dxy_pv_cp = threevec_d_pv_cp.perp();
          float dz_pv_cp = fabs(threevec_d_pv_cp.z());

          //Apply Primary Vertex Charged Particle Distance Selection
          if(dxy_pv_cp>dxy_pv_cp_max) continue;
          if(dz_pv_cp>dz_pv_cp_max) continue;

          //Calculate Distance of Point of Closest Approach (Jet,Charged Particle) with Primary Vertex
          const ThreeVector threevec_jet_cross_cp_cross_jet = cross(threemomentum_jet,threevec_jet_cross_cp);
	        float parameter_PCA;
          if(dot(threevec_jet_cross_cp_cross_jet,threemomentum_cp)!=0) parameter_PCA = dot(threevec_jet_cross_cp_cross_jet,(particlevertex3d-pvertex))/dot(threevec_jet_cross_cp_cross_jet,threemomentum_cp);
	        else parameter_PCA = 0;
	        const float d_PCA_PV = ((parameter_PCA * threemomentum_cp) + (particlevertex3d-pvertex)).mod();

          //Apply Point of Closest Approach (Jet,Charged Particle) Primary Vertex Distance Selection
          if(d_PCA_PV>d_PCA_PV_max) continue;
          
          //Fill Charged Particle Transverse Momentum Histogram without Cut
          _h_ChargedParticlePtUncut[0]->fill(cp.momentum().pT(), weight);
          _h_ChargedParticlePtUncut[jetflavorID]->fill(cp.momentum().pT(), weight);
          
          //Apply Charged Particle Transverse Momentum Selection
          if(cp.momentum().pT()<pt_min_cp) continue;

          //Increment Number of Charged Particles in Jet
          ncparticles++;

	        //Collect selected Charged Particles
          selcparticles.push_back(cp);

          //Calculate Impact Parameter
          float impactparameter = 0;
          if(dot(threemomentum_jet,threevec_d_pv_cp) >= 0) impactparameter = d_pv_cp;
          else impactparameter = -1.*d_pv_cp;

          //Calculate Relative Momentum
	        float relativemomentum = threevec_jet_cross_cp.mod()/threemomentum_jet.mod();

          //Calculate Distance of Particle Vertex to Primary Vertex
	        float vertexdistance = (particlevertex3d-pvertex).mod();
          if(vertexdistance > 0.001) ncpsecvtx++;

          //Fill Histograms
          _h_ChargedParticlePt[0]->fill(cp.momentum().pT(), weight);
          _h_ChargedParticlePt[jetflavorID]->fill(cp.momentum().pT(), weight);
          _h_ChargedParticlePtRel[0]->fill(relativemomentum, weight);
          _h_ChargedParticlePtRel[jetflavorID]->fill(relativemomentum, weight);
          _h_ChargedParticleJetDist[0]->fill(d_jet_cp, weight);
          _h_ChargedParticleJetDist[jetflavorID]->fill(d_jet_cp, weight);
          _h_ChargedParticleJetDr[0]->fill(dr_jet_cp, weight);
          _h_ChargedParticleJetDr[jetflavorID]->fill(dr_jet_cp, weight);
          _h_ChargedParticlePVD[0]->fill(d_pv_cp, weight);
          _h_ChargedParticlePVD[jetflavorID]->fill(d_pv_cp, weight);
          _h_ChargedParticlePVDxy[0]->fill(dxy_pv_cp, weight);
          _h_ChargedParticlePVDxy[jetflavorID]->fill(dxy_pv_cp, weight);
          _h_ChargedParticlePVDz[0]->fill(dz_pv_cp, weight);
          _h_ChargedParticlePVDz[jetflavorID]->fill(dz_pv_cp, weight);
          _h_ChargedParticlePCAPVD[0]->fill(d_PCA_PV, weight);
          _h_ChargedParticlePCAPVD[jetflavorID]->fill(d_PCA_PV, weight);
          _h_ChargedParticleIP[0]->fill(impactparameter, weight);
          _h_ChargedParticleIP[jetflavorID]->fill(impactparameter, weight);
          _h_ChargedTrackVertexPVDist[0]->fill(vertexdistance, weight);
          _h_ChargedTrackVertexPVDist[jetflavorID]->fill(vertexdistance, weight);
        }

	      _h_NChargedParticles[0]->fill(ncparticles, weight);
        _h_NChargedParticles[jetflavorID]->fill(ncparticles, weight);


	      //Secondary Vertex Variables
        _h_NChargedParticlesSecVertex[0]->fill(ncpsecvtx, weight);
        _h_NChargedParticlesSecVertex[jetflavorID]->fill(ncpsecvtx, weight);

	      vector<ThreeVector> vertex_position;
        vector<FourMomentum> vertex_fourmomentum;
        vector<float> sumpt2;
        
        VertexFinder(vertex_position,vertex_fourmomentum,sumpt2,selcparticles,svertexcutoff);
        
        int nsv = 0;
        for(size_t iv=0;iv<vertex_position.size();++iv){
          if((vertex_position[iv]-pvertex).mod()<pvertexcutoff) continue;
          
          ++nsv;
          
          _h_SecVertexMass[0]->fill(vertex_fourmomentum[iv].mass(), weight);
          _h_SecVertexMass[jetflavorID]->fill(vertex_fourmomentum[iv].mass(), weight);
          
          const float dr_sv_jet = deltaR((vertex_position[iv]-pvertex),threemomentum_jet);
          
          if(dr_sv_jet>0.5){
            
            cout << "Jet " << njet <<  ": Delta Secondary Vertex Jet (pv pos): R = " << dr_sv_jet << " Eta = " << deltaEta((vertex_position[iv]-pvertex),threemomentum_jet) << " Phi = " << deltaPhi((vertex_position[iv]-pvertex),threemomentum_jet) << endl;
            cout << "Jet " << njet <<  ": Delta R Secondary Vertex Jet (pv mom): R = " << deltaR(j.momentum(), vertex_fourmomentum[iv]) << " Eta = " << deltaEta(j.momentum(), vertex_fourmomentum[iv]) << " Phi = " << deltaPhi(j.momentum(), vertex_fourmomentum[iv]) << endl;
            
            //cout << "Primary Vertex: X = " << pvertex.x() << " Y = " << pvertex.y() << " Z = " << pvertex.z() << endl;
            //cout << "Vertex " << iv << ": X = " << vertex_position[iv].x() << " Y = " << vertex_position[iv].y() << " Z = " << vertex_position[iv].z() << " M = " << vertex_fourmomentum[iv].mass() << " SumPt2 = " << sumpt2[iv] << endl;
            cout << "Vertex PV Vector " << iv << ": X = " << vertex_position[iv].x()-pvertex.x() << " Y = " << vertex_position[iv].y()-pvertex.y() << " Z = " << vertex_position[iv].z()-pvertex.z() << " M = " << vertex_fourmomentum[iv].mass() << " SumPt2 = " << sumpt2[iv] << endl;
            cout << "Jet " << njet << ": Px = " << j.momentum().x() << " Py = " << j.momentum().y() << " Pz = " << j.momentum().z() << " E = " << j.momentum().z() << " M = " << j.momentum().mass() << endl;
            
            int nscp = 0;
            
            foreach (const Particle& scp, selcparticles){
              const FourMomentum fourmomentum_scp = scp.momentum();
              const ThreeVector threemomentum_scp(fourmomentum_scp.x(),fourmomentum_scp.y(),fourmomentum_scp.z());
            
              cout << "Particle " << nscp <<  ": Delta R Selected CP Jet: " << deltaR(j.momentum(), scp.momentum()) << endl;
              cout << "Particle " << nscp <<  ": Delta R Selected CP Secondary Vertex: " << deltaR((vertex_position[iv]-pvertex), threemomentum_scp) << endl;
              
              nscp++;
            }
          }
          
          _h_SecVertexJetDr[0]->fill(dr_sv_jet, weight);
          _h_SecVertexJetDr[jetflavorID]->fill(dr_sv_jet, weight);
	      }
        
        _h_NSecVertex[0]->fill(nsv, weight);
        _h_NSecVertex[jetflavorID]->fill(nsv, weight);
        
        // Muon Variables
        
        //Get Muons
        Particles leps = applyProjection<ChargedLeptons>(event,"Leptons").chargedLeptons();
        
        foreach (const Particle& lep, leps){
          
          //Select Only Muons
          if(fabs(lep.pid())!=13) continue;
          
          //Lepton Kinematics Selection
          if(lep.momentum().pT()<pt_min_lep) continue;
          if(fabs(lep.momentum().eta())>eta_max_lep) continue;
          
          //Get Lepton Momentum Vector
          const FourMomentum fourmomentum_lep = lep.momentum();
          const ThreeVector threemomentum_lep(fourmomentum_lep.x(),fourmomentum_lep.y(),fourmomentum_lep.z());
          
          //Calculate Lepton Jet Delta R
          float dr_jet_lep = deltaR(j.momentum(), fourmomentum_lep);
          
          //Apply Jet Lepton Delta R Selection
          if(dr_jet_lep>dr_jet_lep_max) continue;
          
          //Calculate Cross Vector for Jet & Lepton
          ThreeVector threevec_jet_cross_lep = cross(threemomentum_jet,threemomentum_lep);
          
          //Calculate Relative Momentum
	        float relativemomentum = threevec_jet_cross_lep.mod()/threemomentum_jet.mod();
          
          _h_MuonJetDr[0]->fill(dr_jet_lep, weight);
          _h_MuonJetDr[jetflavorID]->fill(dr_jet_lep, weight);
          _h_MuonPtRel[0]->fill(relativemomentum, weight);
          _h_MuonPtRel[jetflavorID]->fill(relativemomentum, weight);
        }
      }
    }


    /// Normalise histograms etc., after the run
    void finalize() {
      
      /*
      //Normalization of Histograms
      for(int jetflav=0;jetflav<njetflavors;jetflav++){
        normalize(_h_JetFlavor[jetflav],1.);
        normalize(_h_NParticles[jetflav],1.);
        normalize(_h_NChargedParticles[jetflav],1.);
        normalize(_h_ChargedParticlePt[jetflav],1.);
        normalize(_h_ChargedParticlePtUncut[jetflav],1.);
        normalize(_h_ChargedParticlePtRel[jetflav],1.);
        normalize(_h_ChargedParticleJetDist[jetflav],1.);
        normalize(_h_ChargedParticleJetDr[jetflav],1.);
        normalize(_h_ChargedParticlePVD[jetflav],1.);
        normalize(_h_ChargedParticlePVDxy[jetflav],1.);
        normalize(_h_ChargedParticlePVDz[jetflav],1.);
        normalize(_h_ChargedParticlePCAPVD[jetflav],1.);
        normalize(_h_ChargedParticleIP[jetflav],1.);
        normalize(_h_ChargedTrackVertexPVDist[jetflav],1.);
        normalize(_h_NChargedParticlesSecVertex[jetflav],1.);
        normalize(_h_NSecVertex[jetflav],1.);
        normalize(_h_SecVertexMass[jetflav],1.);
        normalize(_h_SecVertexJetDr[jetflav],1.);
        normalize(_h_MuonPtRel[jetflav],1.);
        normalize(_h_MuonJetDr[jetflav],1.);
      }
      */
      
    }

    //@}
    
    void VertexFinder(vector<ThreeVector>& vertex_position, vector<FourMomentum>& vertex_fourmomentum, vector<float>& sumpt2, const Particles praticles, const float cutoffvalue = 0.001){
      
      for(Particles::const_iterator itp = praticles.begin();itp!=praticles.end();++itp){
	
	      HepMC::ThreeVector HEPMCparticlevertex = itp->genParticle()->production_vertex()->point3d();
	      ThreeVector particlevertex(HEPMCparticlevertex.x(),HEPMCparticlevertex.y(),HEPMCparticlevertex.z());

	      int vertex_vecid = -1;
	      for(size_t iv=0;iv<vertex_position.size();++iv){
	        if((vertex_position[iv]-particlevertex).mod()<cutoffvalue){
	          vertex_vecid = iv;
	          break;
	        }
	      }

	      if(vertex_vecid>=0){
          vertex_fourmomentum[vertex_vecid] += itp->momentum();
          sumpt2[vertex_vecid] += pow(itp->momentum().x(),2)+pow(itp->momentum().y(),2);
        }
	      else{
	        vertex_position.push_back(particlevertex);
	        vertex_fourmomentum.push_back(itp->momentum());
          sumpt2.push_back(pow(itp->momentum().x(),2)+pow(itp->momentum().y(),2));
	      }
      }
    }
    
    
    ThreeVector PVertexFinder(const Particles praticles, const float cutoffvalue = 0.001){
      vector<ThreeVector> vertex_position;
      vector<FourMomentum> vertex_fourmomentum;
      vector<float> sumpt2;
      
      VertexFinder(vertex_position,vertex_fourmomentum,sumpt2,praticles,cutoffvalue);
      
      ThreeVector pv_threevec;
      //float vmass_max = 0.;
      float sumpt2_max = 0.;
      
      for(size_t iv=0;iv<vertex_position.size();++iv){
        //cout << "Vertex " << iv << ": X = " << vertex_position[iv].x() << " Y = " << vertex_position[iv].y() << " Z = " << vertex_position[iv].z() << " M = " << vertex_fourmomentum[iv].mass() << " SumPt2 = " << sumpt2[iv] << endl;
	      /*
        if(vertex_fourmomentum[iv].mass()>vmass_max){
	        pv_threevec = vertex_position[iv];
	        vmass_max = vertex_fourmomentum[iv].mass();
	      }
        */
        if(sumpt2[iv]>sumpt2_max){
	        pv_threevec = vertex_position[iv];
	        sumpt2_max = sumpt2[iv];
	      }
      }
      
      return pv_threevec;
    }


  private:

    int njetflavors;
    int jetflavor[4];
    std::string jetflavorname[4];

    //Vertex Parameters
    const float pvertexcutoff = 0.005;
    const float svertexcutoff = 0.005;
    
    //Jet Selection Parameters
    const float pt_min_jets    = 20.*GeV;
    const float eta_max_jets   = 2.5;
      
    //Charged Particle Selection Parameters
    const float pt_min_cp      = 1.*GeV;
    const float eta_max_cp     = 2.5;
    const float dr_jet_cp_max  = .3;
    const float d_jet_cp_max   = 700*micrometer;
    const float dxy_pv_cp_max  = .2*cm; 
    const float dz_pv_cp_max   = 17.*cm;
    const float d_PCA_PV_max   = 5.*cm;
    
    //Muon Selection Parameters
    const float pt_min_lep     = 1.*GeV;
    const float eta_max_lep    = 2.1;
    const float dr_jet_lep_max  = .3;
    
  private:
    
    Histo1DPtr  _h_JetFlavor[4];                 
    Histo1DPtr  _h_NParticles[4];                
    Histo1DPtr  _h_NChargedParticles[4];         
      
    Histo1DPtr  _h_ChargedParticlePt[4];
    Histo1DPtr  _h_ChargedParticlePtUncut[4];
    Histo1DPtr  _h_ChargedParticlePtRel[4];         
    Histo1DPtr  _h_ChargedParticleJetDist[4];    
    Histo1DPtr  _h_ChargedParticleJetDr[4];      
    Histo1DPtr  _h_ChargedParticlePVD[4];        
    Histo1DPtr  _h_ChargedParticlePVDxy[4];      
    Histo1DPtr  _h_ChargedParticlePVDz[4];
    Histo1DPtr  _h_ChargedParticlePCAPVD[4];     
    Histo1DPtr  _h_ChargedParticleIP[4];
    
    Histo1DPtr  _h_ChargedTrackVertexPVDist[4];   
    Histo1DPtr  _h_NChargedParticlesSecVertex[4];
    Histo1DPtr  _h_NSecVertex[4];
    Histo1DPtr  _h_SecVertexMass[4];   
    Histo1DPtr  _h_SecVertexJetDr[4];
    
    Histo1DPtr  _h_MuonPtRel[4];
    Histo1DPtr  _h_MuonJetDr[4];
  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(BTAG_JET_TRACK_SEL_OLD);

}
