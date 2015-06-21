import FWCore.ParameterSet.Config as cms

process = cms.Process("SumForXsection")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(200) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/mc/Summer12DR53X/TTJets_MSDecays_JpsiFilter_central_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V19-v2/70000/007E74F5-48ED-E411-9925-0025905C2CBA.root'
    )
)

process.sumforxsection = cms.EDAnalyzer('SumForXsection'
)

process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string('histoWeights.root')
                                   )

process.p = cms.Path(process.sumforxsection)
