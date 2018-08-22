    Info<< "Reading transportProperties\n" << endl;

    IOdictionary transportProperties
    (
        IOobject
        (
            "transportProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );

    dimensionedScalar rho0
    (
        transportProperties.lookup("rho0")
    );

//	reference temperature
    dimensionedScalar T0
    (
        transportProperties.lookup("T0")
    );

//	melting temperature
    dimensionedScalar Tm
    (
        transportProperties.lookup("Tm")
    );

//	liquidus temperature, only for alloy case
    dimensionedScalar Tl
    (
        transportProperties.lookup("Tl")
    );

//	solidus temperature, only for alloy case
    dimensionedScalar Ts
    (
        transportProperties.lookup("Ts")
    );

//	latent heat of fusion
    dimensionedScalar L 
    (
        transportProperties.lookup("L")
    );

//	kinematic viscosity
    dimensionedScalar nu
    (
        dimensionedScalar(transportProperties.lookup("mu"))/rho0
    );

//	specific heat
    dimensionedScalar Cp 
    (
        transportProperties.lookup("Cp")
    );

//	thermal conductivity
    dimensionedScalar ktherm 
    (
        transportProperties.lookup("ktherm")
    );

//	thermal diffusivity
    dimensionedScalar DT=ktherm/(rho0*Cp);

//	gravity vector
    dimensionedVector g 
    (
        transportProperties.lookup("g")
    );

//	thermal expansion coefficient
    dimensionedScalar beta
    (
        transportProperties.lookup("beta")
    );

//	constant for velocity source term
    dimensionedScalar C 
    (
        transportProperties.lookup("C")
    );

//	relaxation factor for h iteration
    dimensionedScalar omegaDH 
    (
        transportProperties.lookup("omegaDH")
    );
