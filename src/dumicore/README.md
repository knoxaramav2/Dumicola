# DUMICORE

The bedrock library for a Dumicola system. This layer acts as the 'OS' of a dumicola system, bringing together all of the primary Dumicola components and using them to handle resource management and manage control flow. The Dumicore API provides a set of configuration interfaces for additional control and configuration.

## API

###### General Configuration API
Method | Type | Args | Description
------ | ---- | ---- | -----------


###### Service API
Method | Type | Args | Description
------ | ---- | ---- | -----------
RegisterNetworkService | bool | INetworkService | Set network service 
RegisterDbService | bool | IDbService | Set database service
RegisterInstanceService | bool | IService | Register service with new instance per request
RegisterScopedService | bool | IService | Register service with container lifespan
RegisterLifetimeService | bool | IService | Register service with program lifespan 
GetService | IService | <T:IService> | Return instance handle of service
GetScopedProvider | IScopedProvider |  | Return current service provider


## Build Flags
Flag | Values | Description
---- | ------ | -----------



