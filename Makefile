#
# OMNeT++/OMNEST Makefile for CastaliaBin
#
# This file was generated with the command:
#  opp_makemake -f -r --deep -o CastaliaBin -u Cmdenv -P /home/manolis/omnetpp-4.6/Castalia -M release -X Simulations -X out -X bin
#

# Name of target to be created (-o option)
TARGET = CastaliaBin$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
#USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Isrc \
    -Isrc/energySource \
    -Isrc/energySource/traceEnergySource \
    -Isrc/helpStructures \
    -Isrc/node \
    -Isrc/node/application \
    -Isrc/node/application/bridgeTest \
    -Isrc/node/application/connectivityMap \
    -Isrc/node/application/multiRingsApp \
    -Isrc/node/application/myApp \
    -Isrc/node/application/simpleAggregation \
    -Isrc/node/application/testmultiRingsApp \
    -Isrc/node/application/throughputTest \
    -Isrc/node/application/valuePropagation \
    -Isrc/node/application/valueReporting \
    -Isrc/node/communication \
    -Isrc/node/communication/mac \
    -Isrc/node/communication/mac/baselineBanMac \
    -Isrc/node/communication/mac/bypassMac \
    -Isrc/node/communication/mac/mac802154 \
    -Isrc/node/communication/mac/mac802154/staticGTS802154 \
    -Isrc/node/communication/mac/tMac \
    -Isrc/node/communication/mac/tunableMac \
    -Isrc/node/communication/radio \
    -Isrc/node/communication/routing \
    -Isrc/node/communication/routing/bypassRouting \
    -Isrc/node/communication/routing/leach \
    -Isrc/node/communication/routing/multipathRingsRouting \
    -Isrc/node/communication/routing/myAppRouting \
    -Isrc/node/mobilityManager \
    -Isrc/node/mobilityManager/lineMobilityManager \
    -Isrc/node/mobilityManager/noMobilityManager \
    -Isrc/node/resourceManager \
    -Isrc/node/resourceManager/energySubsystem \
    -Isrc/node/resourceManager/energySubsystem/energyHarvester \
    -Isrc/node/resourceManager/energySubsystem/energyHarvester/solarCell \
    -Isrc/node/resourceManager/energySubsystem/energyHarvester/traceHarvester \
    -Isrc/node/resourceManager/energySubsystem/energyHarvester/windTurbine \
    -Isrc/node/resourceManager/energySubsystem/energyManager \
    -Isrc/node/resourceManager/energySubsystem/energyPrediction \
    -Isrc/node/resourceManager/energySubsystem/energyPrediction/aewma \
    -Isrc/node/resourceManager/energySubsystem/energyStorage \
    -Isrc/node/resourceManager/energySubsystem/energyStorage/battery \
    -Isrc/node/resourceManager/energySubsystem/energyStorage/rechargeableBattery \
    -Isrc/node/resourceManager/energySubsystem/energyStorage/supercapacitor \
    -Isrc/node/resourceManager/resourceManager \
    -Isrc/node/sensorManager \
    -Isrc/physicalProcess \
    -Isrc/physicalProcess/carsPhysicalProcess \
    -Isrc/physicalProcess/customizablePhysicalProcess \
    -Isrc/wirelessChannel \
    -Isrc/wirelessChannel/defaultChannel \
    -Isrc/wirelessChannel/traceChannel

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/src/energySource/VirtualEnergySource.o \
    $O/src/energySource/traceEnergySource/TraceEnergySource.o \
    $O/src/helpStructures/CastaliaModule.o \
    $O/src/helpStructures/DebugInfoWriter.o \
    $O/src/helpStructures/TimerService.o \
    $O/src/node/application/VirtualApplication.o \
    $O/src/node/application/bridgeTest/BridgeTest.o \
    $O/src/node/application/connectivityMap/ConnectivityMap.o \
    $O/src/node/application/multiRingsApp/MultiRingsApp.o \
    $O/src/node/application/myApp/MyApp.o \
    $O/src/node/application/simpleAggregation/SimpleAggregation.o \
    $O/src/node/application/testmultiRingsApp/TestmultiRingsApp.o \
    $O/src/node/application/throughputTest/ThroughputTest.o \
    $O/src/node/application/valuePropagation/ValuePropagation.o \
    $O/src/node/application/valueReporting/ValueReporting.o \
    $O/src/node/communication/mac/VirtualMac.o \
    $O/src/node/communication/mac/baselineBanMac/BaselineBANMac.o \
    $O/src/node/communication/mac/bypassMac/BypassMAC.o \
    $O/src/node/communication/mac/mac802154/Basic802154.o \
    $O/src/node/communication/mac/mac802154/staticGTS802154/StaticGTS802154.o \
    $O/src/node/communication/mac/tMac/TMAC.o \
    $O/src/node/communication/mac/tunableMac/TunableMAC.o \
    $O/src/node/communication/radio/Radio.o \
    $O/src/node/communication/radio/RadioSupportFunctions.o \
    $O/src/node/communication/routing/VirtualRouting.o \
    $O/src/node/communication/routing/bypassRouting/BypassRouting.o \
    $O/src/node/communication/routing/multipathRingsRouting/MultipathRingsRouting.o \
    $O/src/node/communication/routing/myAppRouting/MyAppRouting.o \
    $O/src/node/mobilityManager/VirtualMobilityManager.o \
    $O/src/node/mobilityManager/lineMobilityManager/LineMobilityManager.o \
    $O/src/node/mobilityManager/noMobilityManager/NoMobilityManager.o \
    $O/src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.o \
    $O/src/node/resourceManager/energySubsystem/energyHarvester/solarCell/SolarCell.o \
    $O/src/node/resourceManager/energySubsystem/energyHarvester/traceHarvester/TraceHarvester.o \
    $O/src/node/resourceManager/energySubsystem/energyHarvester/windTurbine/WindTurbine.o \
    $O/src/node/resourceManager/energySubsystem/energyManager/DefaultEnergyManager.o \
    $O/src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.o \
    $O/src/node/resourceManager/energySubsystem/energyPrediction/VirtualEnergyPredictor.o \
    $O/src/node/resourceManager/energySubsystem/energyPrediction/aewma/AEWMA.o \
    $O/src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.o \
    $O/src/node/resourceManager/energySubsystem/energyStorage/battery/Battery.o \
    $O/src/node/resourceManager/energySubsystem/energyStorage/rechargeableBattery/RechargeableBattery.o \
    $O/src/node/resourceManager/energySubsystem/energyStorage/supercapacitor/Supercapacitor.o \
    $O/src/node/resourceManager/resourceManager/ResourceManager.o \
    $O/src/node/sensorManager/SensorManager.o \
    $O/src/physicalProcess/carsPhysicalProcess/CarsPhysicalProcess.o \
    $O/src/physicalProcess/customizablePhysicalProcess/CustomizablePhysicalProcess.o \
    $O/src/wirelessChannel/defaultChannel/WirelessChannel.o \
    $O/src/wirelessChannel/defaultChannel/WirelessChannelTemporal.o \
    $O/src/wirelessChannel/traceChannel/TraceChannel.o \
    $O/src/helpStructures/TimerServiceMessage_m.o \
    $O/src/node/application/ApplicationPacket_m.o \
    $O/src/node/application/multiRingsApp/MultiRingDataPacket_m.o \
    $O/src/node/application/valueReporting/ValueReportingPacket_m.o \
    $O/src/node/communication/mac/MacPacket_m.o \
    $O/src/node/communication/mac/baselineBanMac/BaselineMacPacket_m.o \
    $O/src/node/communication/mac/mac802154/Basic802154Packet_m.o \
    $O/src/node/communication/mac/tMac/TMacPacket_m.o \
    $O/src/node/communication/mac/tunableMac/TunableMacControl_m.o \
    $O/src/node/communication/mac/tunableMac/TunableMacPacket_m.o \
    $O/src/node/communication/radio/RadioControlMessage_m.o \
    $O/src/node/communication/routing/RoutingPacket_m.o \
    $O/src/node/communication/routing/bypassRouting/BypassRoutingPacket_m.o \
    $O/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingControl_m.o \
    $O/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingPacket_m.o \
    $O/src/node/communication/routing/myAppRouting/MyAppRoutingPacket_m.o \
    $O/src/node/mobilityManager/MobilityManagerMessage_m.o \
    $O/src/node/resourceManager/ResourceManagerMessage_m.o \
    $O/src/node/sensorManager/SensorManagerMessage_m.o \
    $O/src/physicalProcess/PhysicalProcessMessage_m.o \
    $O/src/wirelessChannel/WirelessChannelMessages_m.o

# Message files
MSGFILES = \
    src/helpStructures/TimerServiceMessage.msg \
    src/node/application/ApplicationPacket.msg \
    src/node/application/multiRingsApp/MultiRingDataPacket.msg \
    src/node/application/valueReporting/ValueReportingPacket.msg \
    src/node/communication/mac/MacPacket.msg \
    src/node/communication/mac/baselineBanMac/BaselineMacPacket.msg \
    src/node/communication/mac/mac802154/Basic802154Packet.msg \
    src/node/communication/mac/tMac/TMacPacket.msg \
    src/node/communication/mac/tunableMac/TunableMacControl.msg \
    src/node/communication/mac/tunableMac/TunableMacPacket.msg \
    src/node/communication/radio/RadioControlMessage.msg \
    src/node/communication/routing/RoutingPacket.msg \
    src/node/communication/routing/bypassRouting/BypassRoutingPacket.msg \
    src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingControl.msg \
    src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingPacket.msg \
    src/node/communication/routing/myAppRouting/MyAppRoutingPacket.msg \
    src/node/mobilityManager/MobilityManagerMessage.msg \
    src/node/resourceManager/ResourceManagerMessage.msg \
    src/node/sensorManager/SensorManagerMessage.msg \
    src/physicalProcess/PhysicalProcessMessage.msg \
    src/wirelessChannel/WirelessChannelMessages.msg

# Default mode (-M option); can be overridden with make MODE=debug (or =release)
ifndef MODE
MODE = release
endif

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f CastaliaBin CastaliaBin.exe libCastaliaBin.so libCastaliaBin.a libCastaliaBin.dll libCastaliaBin.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f src/*_m.cc src/*_m.h
	$(Q)-rm -f src/energySource/*_m.cc src/energySource/*_m.h
	$(Q)-rm -f src/energySource/traceEnergySource/*_m.cc src/energySource/traceEnergySource/*_m.h
	$(Q)-rm -f src/helpStructures/*_m.cc src/helpStructures/*_m.h
	$(Q)-rm -f src/node/*_m.cc src/node/*_m.h
	$(Q)-rm -f src/node/application/*_m.cc src/node/application/*_m.h
	$(Q)-rm -f src/node/application/bridgeTest/*_m.cc src/node/application/bridgeTest/*_m.h
	$(Q)-rm -f src/node/application/connectivityMap/*_m.cc src/node/application/connectivityMap/*_m.h
	$(Q)-rm -f src/node/application/multiRingsApp/*_m.cc src/node/application/multiRingsApp/*_m.h
	$(Q)-rm -f src/node/application/myApp/*_m.cc src/node/application/myApp/*_m.h
	$(Q)-rm -f src/node/application/simpleAggregation/*_m.cc src/node/application/simpleAggregation/*_m.h
	$(Q)-rm -f src/node/application/testmultiRingsApp/*_m.cc src/node/application/testmultiRingsApp/*_m.h
	$(Q)-rm -f src/node/application/throughputTest/*_m.cc src/node/application/throughputTest/*_m.h
	$(Q)-rm -f src/node/application/valuePropagation/*_m.cc src/node/application/valuePropagation/*_m.h
	$(Q)-rm -f src/node/application/valueReporting/*_m.cc src/node/application/valueReporting/*_m.h
	$(Q)-rm -f src/node/communication/*_m.cc src/node/communication/*_m.h
	$(Q)-rm -f src/node/communication/mac/*_m.cc src/node/communication/mac/*_m.h
	$(Q)-rm -f src/node/communication/mac/baselineBanMac/*_m.cc src/node/communication/mac/baselineBanMac/*_m.h
	$(Q)-rm -f src/node/communication/mac/bypassMac/*_m.cc src/node/communication/mac/bypassMac/*_m.h
	$(Q)-rm -f src/node/communication/mac/mac802154/*_m.cc src/node/communication/mac/mac802154/*_m.h
	$(Q)-rm -f src/node/communication/mac/mac802154/staticGTS802154/*_m.cc src/node/communication/mac/mac802154/staticGTS802154/*_m.h
	$(Q)-rm -f src/node/communication/mac/tMac/*_m.cc src/node/communication/mac/tMac/*_m.h
	$(Q)-rm -f src/node/communication/mac/tunableMac/*_m.cc src/node/communication/mac/tunableMac/*_m.h
	$(Q)-rm -f src/node/communication/radio/*_m.cc src/node/communication/radio/*_m.h
	$(Q)-rm -f src/node/communication/routing/*_m.cc src/node/communication/routing/*_m.h
	$(Q)-rm -f src/node/communication/routing/bypassRouting/*_m.cc src/node/communication/routing/bypassRouting/*_m.h
	$(Q)-rm -f src/node/communication/routing/leach/*_m.cc src/node/communication/routing/leach/*_m.h
	$(Q)-rm -f src/node/communication/routing/multipathRingsRouting/*_m.cc src/node/communication/routing/multipathRingsRouting/*_m.h
	$(Q)-rm -f src/node/communication/routing/myAppRouting/*_m.cc src/node/communication/routing/myAppRouting/*_m.h
	$(Q)-rm -f src/node/mobilityManager/*_m.cc src/node/mobilityManager/*_m.h
	$(Q)-rm -f src/node/mobilityManager/lineMobilityManager/*_m.cc src/node/mobilityManager/lineMobilityManager/*_m.h
	$(Q)-rm -f src/node/mobilityManager/noMobilityManager/*_m.cc src/node/mobilityManager/noMobilityManager/*_m.h
	$(Q)-rm -f src/node/resourceManager/*_m.cc src/node/resourceManager/*_m.h
	$(Q)-rm -f src/node/resourceManager/energySubsystem/*_m.cc src/node/resourceManager/energySubsystem/*_m.h
	$(Q)-rm -f src/node/resourceManager/energySubsystem/energyHarvester/*_m.cc src/node/resourceManager/energySubsystem/energyHarvester/*_m.h
	$(Q)-rm -f src/node/resourceManager/energySubsystem/energyHarvester/solarCell/*_m.cc src/node/resourceManager/energySubsystem/energyHarvester/solarCell/*_m.h
	$(Q)-rm -f src/node/resourceManager/energySubsystem/energyHarvester/traceHarvester/*_m.cc src/node/resourceManager/energySubsystem/energyHarvester/traceHarvester/*_m.h
	$(Q)-rm -f src/node/resourceManager/energySubsystem/energyHarvester/windTurbine/*_m.cc src/node/resourceManager/energySubsystem/energyHarvester/windTurbine/*_m.h
	$(Q)-rm -f src/node/resourceManager/energySubsystem/energyManager/*_m.cc src/node/resourceManager/energySubsystem/energyManager/*_m.h
	$(Q)-rm -f src/node/resourceManager/energySubsystem/energyPrediction/*_m.cc src/node/resourceManager/energySubsystem/energyPrediction/*_m.h
	$(Q)-rm -f src/node/resourceManager/energySubsystem/energyPrediction/aewma/*_m.cc src/node/resourceManager/energySubsystem/energyPrediction/aewma/*_m.h
	$(Q)-rm -f src/node/resourceManager/energySubsystem/energyStorage/*_m.cc src/node/resourceManager/energySubsystem/energyStorage/*_m.h
	$(Q)-rm -f src/node/resourceManager/energySubsystem/energyStorage/battery/*_m.cc src/node/resourceManager/energySubsystem/energyStorage/battery/*_m.h
	$(Q)-rm -f src/node/resourceManager/energySubsystem/energyStorage/rechargeableBattery/*_m.cc src/node/resourceManager/energySubsystem/energyStorage/rechargeableBattery/*_m.h
	$(Q)-rm -f src/node/resourceManager/energySubsystem/energyStorage/supercapacitor/*_m.cc src/node/resourceManager/energySubsystem/energyStorage/supercapacitor/*_m.h
	$(Q)-rm -f src/node/resourceManager/resourceManager/*_m.cc src/node/resourceManager/resourceManager/*_m.h
	$(Q)-rm -f src/node/sensorManager/*_m.cc src/node/sensorManager/*_m.h
	$(Q)-rm -f src/physicalProcess/*_m.cc src/physicalProcess/*_m.h
	$(Q)-rm -f src/physicalProcess/carsPhysicalProcess/*_m.cc src/physicalProcess/carsPhysicalProcess/*_m.h
	$(Q)-rm -f src/physicalProcess/customizablePhysicalProcess/*_m.cc src/physicalProcess/customizablePhysicalProcess/*_m.h
	$(Q)-rm -f src/wirelessChannel/*_m.cc src/wirelessChannel/*_m.h
	$(Q)-rm -f src/wirelessChannel/defaultChannel/*_m.cc src/wirelessChannel/defaultChannel/*_m.h
	$(Q)-rm -f src/wirelessChannel/traceChannel/*_m.cc src/wirelessChannel/traceChannel/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc src/*.cc src/energySource/*.cc src/energySource/traceEnergySource/*.cc src/helpStructures/*.cc src/node/*.cc src/node/application/*.cc src/node/application/bridgeTest/*.cc src/node/application/connectivityMap/*.cc src/node/application/multiRingsApp/*.cc src/node/application/myApp/*.cc src/node/application/simpleAggregation/*.cc src/node/application/testmultiRingsApp/*.cc src/node/application/throughputTest/*.cc src/node/application/valuePropagation/*.cc src/node/application/valueReporting/*.cc src/node/communication/*.cc src/node/communication/mac/*.cc src/node/communication/mac/baselineBanMac/*.cc src/node/communication/mac/bypassMac/*.cc src/node/communication/mac/mac802154/*.cc src/node/communication/mac/mac802154/staticGTS802154/*.cc src/node/communication/mac/tMac/*.cc src/node/communication/mac/tunableMac/*.cc src/node/communication/radio/*.cc src/node/communication/routing/*.cc src/node/communication/routing/bypassRouting/*.cc src/node/communication/routing/leach/*.cc src/node/communication/routing/multipathRingsRouting/*.cc src/node/communication/routing/myAppRouting/*.cc src/node/mobilityManager/*.cc src/node/mobilityManager/lineMobilityManager/*.cc src/node/mobilityManager/noMobilityManager/*.cc src/node/resourceManager/*.cc src/node/resourceManager/energySubsystem/*.cc src/node/resourceManager/energySubsystem/energyHarvester/*.cc src/node/resourceManager/energySubsystem/energyHarvester/solarCell/*.cc src/node/resourceManager/energySubsystem/energyHarvester/traceHarvester/*.cc src/node/resourceManager/energySubsystem/energyHarvester/windTurbine/*.cc src/node/resourceManager/energySubsystem/energyManager/*.cc src/node/resourceManager/energySubsystem/energyPrediction/*.cc src/node/resourceManager/energySubsystem/energyPrediction/aewma/*.cc src/node/resourceManager/energySubsystem/energyStorage/*.cc src/node/resourceManager/energySubsystem/energyStorage/battery/*.cc src/node/resourceManager/energySubsystem/energyStorage/rechargeableBattery/*.cc src/node/resourceManager/energySubsystem/energyStorage/supercapacitor/*.cc src/node/resourceManager/resourceManager/*.cc src/node/sensorManager/*.cc src/physicalProcess/*.cc src/physicalProcess/carsPhysicalProcess/*.cc src/physicalProcess/customizablePhysicalProcess/*.cc src/wirelessChannel/*.cc src/wirelessChannel/defaultChannel/*.cc src/wirelessChannel/traceChannel/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/src/energySource/VirtualEnergySource.o: src/energySource/VirtualEnergySource.cc \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/energySource/VirtualEnergySource.h
$O/src/energySource/traceEnergySource/TraceEnergySource.o: src/energySource/traceEnergySource/TraceEnergySource.cc \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/helpStructures/CastaliaModule.h \
  src/energySource/traceEnergySource/TraceEnergySource.h \
  src/energySource/VirtualEnergySource.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h
$O/src/helpStructures/CastaliaModule.o: src/helpStructures/CastaliaModule.cc \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/helpStructures/CastaliaModule.h
$O/src/helpStructures/DebugInfoWriter.o: src/helpStructures/DebugInfoWriter.cc \
  src/helpStructures/DebugInfoWriter.h
$O/src/helpStructures/TimerService.o: src/helpStructures/TimerService.cc \
  src/helpStructures/TimerServiceMessage_m.h \
  src/helpStructures/TimerService.h \
  src/CastaliaMessages.h
$O/src/node/application/VirtualApplication.o: src/node/application/VirtualApplication.cc \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/radio/Radio.h \
  src/helpStructures/TimerService.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/node/application/ApplicationPacket_m.h \
  src/node/application/VirtualApplication.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/helpStructures/CastaliaModule.h \
  src/node/sensorManager/SensorManagerMessage_m.h
$O/src/node/application/bridgeTest/BridgeTest.o: src/node/application/bridgeTest/BridgeTest.cc \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/helpStructures/CastaliaModule.h \
  src/node/sensorManager/SensorManagerMessage_m.h \
  src/node/application/ApplicationPacket_m.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/application/bridgeTest/BridgeTest.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/application/VirtualApplication.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h \
  src/helpStructures/TimerService.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/node/communication/radio/Radio.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/helpStructures/TimerServiceMessage_m.h
$O/src/node/application/connectivityMap/ConnectivityMap.o: src/node/application/connectivityMap/ConnectivityMap.cc \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/radio/Radio.h \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/helpStructures/TimerService.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/application/VirtualApplication.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/application/ApplicationPacket_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/sensorManager/SensorManagerMessage_m.h \
  src/node/application/connectivityMap/ConnectivityMap.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h
$O/src/node/application/multiRingsApp/MultiRingsApp.o: src/node/application/multiRingsApp/MultiRingsApp.cc \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/helpStructures/TimerService.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/radio/Radio.h \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/node/sensorManager/SensorManagerMessage_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/application/multiRingsApp/MultiRingsApp.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/application/multiRingsApp/MultiRingDataPacket_m.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/application/VirtualApplication.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h \
  src/node/application/ApplicationPacket_m.h
$O/src/node/application/myApp/MyApp.o: src/node/application/myApp/MyApp.cc \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/application/VirtualApplication.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/application/ApplicationPacket_m.h \
  src/node/sensorManager/SensorManagerMessage_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/Radio.h \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/node/application/myApp/MyApp.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/helpStructures/TimerService.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h
$O/src/node/application/simpleAggregation/SimpleAggregation.o: src/node/application/simpleAggregation/SimpleAggregation.cc \
  src/helpStructures/TimerService.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/Radio.h \
  src/node/application/simpleAggregation/SimpleAggregation.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/helpStructures/CastaliaModule.h \
  src/node/sensorManager/SensorManagerMessage_m.h \
  src/node/application/ApplicationPacket_m.h \
  src/node/application/VirtualApplication.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h \
  src/node/resourceManager/resourceManager/ResourceManager.h
$O/src/node/application/testmultiRingsApp/TestmultiRingsApp.o: src/node/application/testmultiRingsApp/TestmultiRingsApp.cc \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/node/sensorManager/SensorManagerMessage_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/application/ApplicationPacket_m.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/application/VirtualApplication.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h \
  src/helpStructures/TimerService.h \
  src/node/application/testmultiRingsApp/TestmultiRingsApp.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/node/communication/radio/Radio.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/mac/MacPacket_m.h \
  src/helpStructures/TimerServiceMessage_m.h
$O/src/node/application/throughputTest/ThroughputTest.o: src/node/application/throughputTest/ThroughputTest.cc \
  src/node/application/ApplicationPacket_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/application/VirtualApplication.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/helpStructures/CastaliaModule.h \
  src/node/sensorManager/SensorManagerMessage_m.h \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/radio/Radio.h \
  src/helpStructures/TimerService.h \
  src/node/application/throughputTest/ThroughputTest.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h
$O/src/node/application/valuePropagation/ValuePropagation.o: src/node/application/valuePropagation/ValuePropagation.cc \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/application/VirtualApplication.h \
  src/node/application/ApplicationPacket_m.h \
  src/node/sensorManager/SensorManagerMessage_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/application/valuePropagation/ValuePropagation.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/node/communication/radio/Radio.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h \
  src/helpStructures/TimerService.h
$O/src/node/application/valueReporting/ValueReporting.o: src/node/application/valueReporting/ValueReporting.cc \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/radio/Radio.h \
  src/node/application/valueReporting/ValueReportingPacket_m.h \
  src/helpStructures/TimerService.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/node/application/ApplicationPacket_m.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/application/VirtualApplication.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/application/valueReporting/ValueReporting.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/node/sensorManager/SensorManagerMessage_m.h \
  src/helpStructures/CastaliaModule.h
$O/src/node/communication/mac/VirtualMac.o: src/node/communication/mac/VirtualMac.cc \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/communication/routing/RoutingPacket_m.h \
  src/node/communication/radio/Radio.h \
  src/node/communication/mac/VirtualMac.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/helpStructures/TimerService.h
$O/src/node/communication/mac/baselineBanMac/BaselineBANMac.o: src/node/communication/mac/baselineBanMac/BaselineBANMac.cc \
  src/helpStructures/CastaliaModule.h \
  src/node/communication/routing/RoutingPacket_m.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/communication/mac/baselineBanMac/BaselineMacPacket_m.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/helpStructures/TimerService.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/Radio.h \
  src/node/communication/mac/VirtualMac.h \
  src/node/communication/mac/baselineBanMac/BaselineBANMac.h
$O/src/node/communication/mac/bypassMac/BypassMAC.o: src/node/communication/mac/bypassMac/BypassMAC.cc \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/communication/routing/RoutingPacket_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/communication/radio/Radio.h \
  src/node/communication/mac/VirtualMac.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/mac/bypassMac/BypassMAC.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/helpStructures/TimerService.h \
  src/node/communication/radio/RadioControlMessage_m.h
$O/src/node/communication/mac/mac802154/Basic802154.o: src/node/communication/mac/mac802154/Basic802154.cc \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/helpStructures/TimerService.h \
  src/node/communication/mac/VirtualMac.h \
  src/node/communication/radio/Radio.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/helpStructures/CastaliaModule.h \
  src/node/communication/routing/RoutingPacket_m.h \
  src/node/communication/mac/mac802154/Basic802154Packet_m.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/communication/mac/mac802154/Basic802154.h
$O/src/node/communication/mac/mac802154/staticGTS802154/StaticGTS802154.o: src/node/communication/mac/mac802154/staticGTS802154/StaticGTS802154.cc \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/node/communication/mac/mac802154/staticGTS802154/StaticGTS802154.h \
  src/helpStructures/TimerService.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/radio/Radio.h \
  src/node/communication/mac/VirtualMac.h \
  src/helpStructures/CastaliaModule.h \
  src/node/communication/routing/RoutingPacket_m.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/communication/mac/mac802154/Basic802154.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/communication/mac/mac802154/Basic802154Packet_m.h
$O/src/node/communication/mac/tMac/TMAC.o: src/node/communication/mac/tMac/TMAC.cc \
  src/helpStructures/TimerService.h \
  src/node/communication/mac/tMac/TMacPacket_m.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/mac/MacPacket_m.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/radio/Radio.h \
  src/node/communication/mac/VirtualMac.h \
  src/node/communication/routing/RoutingPacket_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/communication/mac/tMac/TMAC.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/resourceManager/resourceManager/ResourceManager.h
$O/src/node/communication/mac/tunableMac/TunableMAC.o: src/node/communication/mac/tunableMac/TunableMAC.cc \
  src/node/communication/radio/Radio.h \
  src/node/communication/mac/VirtualMac.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/mac/MacPacket_m.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/mac/tunableMac/TunableMacPacket_m.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/CastaliaMessages.h \
  src/node/communication/mac/tunableMac/TunableMacControl_m.h \
  src/helpStructures/DebugInfoWriter.h \
  src/helpStructures/TimerService.h \
  src/node/communication/mac/tunableMac/TunableMAC.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/communication/routing/RoutingPacket_m.h
$O/src/node/communication/radio/Radio.o: src/node/communication/radio/Radio.cc \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/helpStructures/CastaliaModule.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/Radio.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h
$O/src/node/communication/radio/RadioSupportFunctions.o: src/node/communication/radio/RadioSupportFunctions.cc \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/CastaliaMessages.h
$O/src/node/communication/routing/VirtualRouting.o: src/node/communication/routing/VirtualRouting.cc \
  src/helpStructures/CastaliaModule.h \
  src/node/communication/routing/RoutingPacket_m.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/application/ApplicationPacket_m.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/helpStructures/TimerService.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/radio/Radio.h \
  src/node/communication/routing/VirtualRouting.h
$O/src/node/communication/routing/bypassRouting/BypassRouting.o: src/node/communication/routing/bypassRouting/BypassRouting.cc \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/application/ApplicationPacket_m.h \
  src/node/communication/routing/bypassRouting/BypassRoutingPacket_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/communication/routing/RoutingPacket_m.h \
  src/node/communication/routing/bypassRouting/BypassRouting.h \
  src/node/communication/radio/Radio.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/node/communication/routing/VirtualRouting.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/helpStructures/TimerService.h
$O/src/node/communication/routing/multipathRingsRouting/MultipathRingsRouting.o: src/node/communication/routing/multipathRingsRouting/MultipathRingsRouting.cc \
  src/node/communication/routing/RoutingPacket_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingPacket_m.h \
  src/node/application/ApplicationPacket_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingControl_m.h \
  src/helpStructures/TimerService.h \
  src/node/communication/routing/multipathRingsRouting/MultipathRingsRouting.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h \
  src/node/communication/radio/RadioControlMessage_m.h \
  src/node/communication/routing/VirtualRouting.h \
  src/node/communication/mac/MacPacket_m.h \
  src/node/communication/radio/RadioSupportFunctions.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/communication/radio/Radio.h
$O/src/node/communication/routing/myAppRouting/MyAppRouting.o: src/node/communication/routing/myAppRouting/MyAppRouting.cc
$O/src/node/mobilityManager/VirtualMobilityManager.o: src/node/mobilityManager/VirtualMobilityManager.cc \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h
$O/src/node/mobilityManager/lineMobilityManager/LineMobilityManager.o: src/node/mobilityManager/lineMobilityManager/LineMobilityManager.cc \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/node/mobilityManager/MobilityManagerMessage_m.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/mobilityManager/lineMobilityManager/LineMobilityManager.h \
  src/helpStructures/CastaliaModule.h
$O/src/node/mobilityManager/noMobilityManager/NoMobilityManager.o: src/node/mobilityManager/noMobilityManager/NoMobilityManager.cc \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/mobilityManager/noMobilityManager/NoMobilityManager.h \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h
$O/src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.o: src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.cc \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/node/resourceManager/ResourceManagerMessage_m.h
$O/src/node/resourceManager/energySubsystem/energyHarvester/solarCell/SolarCell.o: src/node/resourceManager/energySubsystem/energyHarvester/solarCell/SolarCell.cc \
  src/node/resourceManager/energySubsystem/energyHarvester/solarCell/SolarCell.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h
$O/src/node/resourceManager/energySubsystem/energyHarvester/traceHarvester/TraceHarvester.o: src/node/resourceManager/energySubsystem/energyHarvester/traceHarvester/TraceHarvester.cc \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/helpStructures/DebugInfoWriter.h \
  src/node/resourceManager/energySubsystem/energyHarvester/traceHarvester/TraceHarvester.h \
  src/CastaliaMessages.h
$O/src/node/resourceManager/energySubsystem/energyHarvester/windTurbine/WindTurbine.o: src/node/resourceManager/energySubsystem/energyHarvester/windTurbine/WindTurbine.cc \
  src/node/resourceManager/energySubsystem/energyHarvester/windTurbine/WindTurbine.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/helpStructures/CastaliaModule.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h
$O/src/node/resourceManager/energySubsystem/energyManager/DefaultEnergyManager.o: src/node/resourceManager/energySubsystem/energyManager/DefaultEnergyManager.cc \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/energySubsystem/energyManager/DefaultEnergyManager.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h
$O/src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.o: src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.cc \
  src/node/resourceManager/energySubsystem/energyStorage/battery/Battery.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/energySubsystem/energyStorage/supercapacitor/Supercapacitor.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h \
  src/node/resourceManager/energySubsystem/energyStorage/rechargeableBattery/RechargeableBattery.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h
$O/src/node/resourceManager/energySubsystem/energyPrediction/VirtualEnergyPredictor.o: src/node/resourceManager/energySubsystem/energyPrediction/VirtualEnergyPredictor.cc \
  src/helpStructures/TimerService.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/node/resourceManager/energySubsystem/energyPrediction/VirtualEnergyPredictor.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h
$O/src/node/resourceManager/energySubsystem/energyPrediction/aewma/AEWMA.o: src/node/resourceManager/energySubsystem/energyPrediction/aewma/AEWMA.cc \
  src/helpStructures/TimerService.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/node/resourceManager/energySubsystem/energyPrediction/VirtualEnergyPredictor.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/helpStructures/TimerServiceMessage_m.h \
  src/node/resourceManager/energySubsystem/energyPrediction/aewma/AEWMA.h \
  src/node/resourceManager/energySubsystem/energyHarvester/VirtualEnergyHarvester.h \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/resourceManager/energySubsystem/energyManager/VirtualEnergyManager.h \
  src/node/resourceManager/resourceManager/ResourceManager.h
$O/src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.o: src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.cc \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/ResourceManagerMessage_m.h
$O/src/node/resourceManager/energySubsystem/energyStorage/battery/Battery.o: src/node/resourceManager/energySubsystem/energyStorage/battery/Battery.cc \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/energySubsystem/energyStorage/battery/Battery.h
$O/src/node/resourceManager/energySubsystem/energyStorage/rechargeableBattery/RechargeableBattery.o: src/node/resourceManager/energySubsystem/energyStorage/rechargeableBattery/RechargeableBattery.cc \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/resourceManager/energySubsystem/energyStorage/rechargeableBattery/RechargeableBattery.h \
  src/node/resourceManager/resourceManager/ResourceManager.h
$O/src/node/resourceManager/energySubsystem/energyStorage/supercapacitor/Supercapacitor.o: src/node/resourceManager/energySubsystem/energyStorage/supercapacitor/Supercapacitor.cc \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/energySubsystem/energyStorage/supercapacitor/Supercapacitor.h \
  src/node/resourceManager/energySubsystem/energyStorage/VirtualEnergyStorage.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h
$O/src/node/resourceManager/resourceManager/ResourceManager.o: src/node/resourceManager/resourceManager/ResourceManager.cc \
  src/node/resourceManager/resourceManager/ResourceManager.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/helpStructures/CastaliaModule.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h
$O/src/node/sensorManager/SensorManager.o: src/node/sensorManager/SensorManager.cc \
  src/physicalProcess/PhysicalProcessMessage_m.h \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/node/sensorManager/SensorManager.h \
  src/node/sensorManager/SensorManagerMessage_m.h \
  src/helpStructures/CastaliaModule.h
$O/src/physicalProcess/carsPhysicalProcess/CarsPhysicalProcess.o: src/physicalProcess/carsPhysicalProcess/CarsPhysicalProcess.cc \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/physicalProcess/carsPhysicalProcess/CarsPhysicalProcess.h \
  src/CastaliaMessages.h \
  src/helpStructures/DebugInfoWriter.h \
  src/physicalProcess/PhysicalProcessMessage_m.h
$O/src/physicalProcess/customizablePhysicalProcess/CustomizablePhysicalProcess.o: src/physicalProcess/customizablePhysicalProcess/CustomizablePhysicalProcess.cc \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/physicalProcess/customizablePhysicalProcess/CustomizablePhysicalProcess.h \
  src/helpStructures/CastaliaModule.h \
  src/physicalProcess/PhysicalProcessMessage_m.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h
$O/src/wirelessChannel/defaultChannel/WirelessChannel.o: src/wirelessChannel/defaultChannel/WirelessChannel.cc \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h \
  src/node/mobilityManager/VirtualMobilityManager.h \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/wirelessChannel/defaultChannel/WirelessChannelTemporal.h \
  src/wirelessChannel/defaultChannel/WirelessChannel.h
$O/src/wirelessChannel/defaultChannel/WirelessChannelTemporal.o: src/wirelessChannel/defaultChannel/WirelessChannelTemporal.cc \
  src/wirelessChannel/defaultChannel/WirelessChannelTemporal.h
$O/src/wirelessChannel/traceChannel/TraceChannel.o: src/wirelessChannel/traceChannel/TraceChannel.cc \
  src/helpStructures/CastaliaModule.h \
  src/node/resourceManager/ResourceManagerMessage_m.h \
  src/wirelessChannel/WirelessChannelMessages_m.h \
  src/wirelessChannel/defaultChannel/WirelessChannelTemporal.h \
  src/wirelessChannel/traceChannel/TraceChannel.h \
  src/helpStructures/DebugInfoWriter.h \
  src/CastaliaMessages.h
