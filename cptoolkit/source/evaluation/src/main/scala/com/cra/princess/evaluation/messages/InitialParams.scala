package com.cra.princess.evaluation.messages

case class CpInitialParams(SearchRegion: SearchRegionType,
                           Origin: LatLon,
                           Destination: LatLon,
                           DVLSensorPerturbations: List[DvlSensorPerturbationType],
                           PerturbingCurrents: List[PerturbingCurrentType],
                           Adaptation: Boolean) extends ToJson
object CpInitialParams extends FromJson[CpInitialParams]

case class SearchRegionType(LowerLeftLocation: LatLon, UpperRightLocation: LatLon, ObjectLocation: LatLon) extends ToJson
object SearchRegionType extends FromJson[SearchRegionType]