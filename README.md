# Dumicola
A networked device control hub for tinkerers. Dumicola provides a managed way to connect devices, provide utilites to create custom programs to automate signaling between devices on your Dumicola network, and create your own libraries and plugins to fully customize your network.

### Use Cases
###### Robotics / Embedded Systems
* Run Microcola on embedded systems to enable interoperability to mobile and desktop environments
* Standardize comunication between robots and other embedded solutions 
###### Home Security
* Steam camera feeds across devices
* Create networked motion sensors
* Broadcast alarms to mobile devices
###### Hobby Projects
* Pretty much any involving computers and networks, really.

## Getting Started

## Connecting Devices

## Basic Programs

## Custom Plugins

## Standard Libraries (CoLib)
* Vulkan (Logic)
* Hypatia (Math)
* Porus (Data Provider)

## DumiSDK
Dumicore is the scaffold for creating custom plugins. This provides everything necessary to create custom component libraries to be used to create extended Dumicola programs.

## DumiCommon
Provides the common libraries required for a dumicola runtime.

## DumiManager
The desktop network manager and program designer. This communicates with Megacola to modify control behavior and start and stop programs. DumiManager also providers a visual environment for viewing device program behavior through customizeable dashboards.

## ColaCore
The base runtime library for Dumicola. Provides minimal required functionality for a Dumicola runtime executable. Service implementations are not provided; these must be registered by the implementing runtime application.

## Megacola
The desktop version of the dumicola runtime. This is the full featured version application for managing network devices and running applications. 

## Microcola
The embedded version of the dumicola runtime. This can be extended for customized use. cased.

# Roadmap

Project | Status | Progress | Active
--------|--------|----------|-------
| DumiCommon | Not Started | ![](https://progress-bar.dev/0/) | No |
| DumiSDK | Not Started | ![](https://progress-bar.dev/0/) | No |
| ColaCore | Not Started | ![](https://progress-bar.dev/0/) | No |
| Megacola | Not Started | ![](https://progress-bar.dev/0/) | No |
| DumiManager | Not Started | ![](https://progress-bar.dev/0/) | No |
| Microcola | Not Started | ![](https://progress-bar.dev/0/) | No |
| Vulkan (STL) | Not Started | ![](https://progress-bar.dev/0/) | No |
| Hypatia (STL) | Not Started | ![](https://progress-bar.dev/0/) | No |
| Porus (STL) | Not Started | ![](https://progress-bar.dev/0/) | No |


###### DumiCommon Progress
- [ ] Database Context
- [ ] DAO
- [ ] Database Models
- [ ] Migrations Manager
- [ ] Security Manager
- [ ] CommonConfig

###### DumiSDK
 - [ ] CommonUtil
 - [ ] NodeBaseImpl
 - [ ] Types
 - [ ] ITypes
 - [ ] Exception

 ###### ColaCore
 - [ ] Process Manager
 - [ ] Resource Manager
 - [ ] Interop Service
 - [ ] Data Service
 - [ ] Network Service
 - [ ] Bytecode Executor

 ###### MegaCola (ColaCore)


 ###### DumiManager
 - [ ] Plugin Manager
 - [ ] App Designer
 - [ ] Network Viewer
 - [ ] Account Administration
 - [ ] Interop Manager

 ###### MicroCola (ColaCore)


 ###### 