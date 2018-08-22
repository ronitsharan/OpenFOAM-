    Info << "Reading field p\n" << endl;
    volScalarField p
    (
        IOobject
        (
            "p",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    Info<< "Reading field T\n" << endl;
    volScalarField T
    (
        IOobject
        (
            "T",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    volScalarField h = Cp*T;

    volScalarField lf
    (
        IOobject
        (
            "lf",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar("lf", dimless, 0)
    );

    Info << "Reading field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

#   include "createPhi.H"


    label pRefCell = 0;
    scalar pRefValue = 0.0;
    setRefCell(p, mesh.solutionDict().subDict("SIMPLE"), pRefCell, pRefValue);
//    setRefCell(p, mesh.solutionDict().subDict("PISO"), pRefCell, pRefValue);

    Info<< "Reading/calculating field rho\n" << endl;
    volScalarField rho
    (
        IOobject
        (
            "rho",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        rho0*(scalar(1) - beta*(T - T0))
    );

    volScalarField A = -C*sqr(scalar(1)-lf)/(rho*(pow(lf,scalar(3))+scalar(5e-3)));

    volScalarField ST 
    (
        IOobject
        (
            "ST",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar("ST", dimTemperature/dimTime, 0)
    );

    volScalarField STconv 
    (
        IOobject
        (
            "STconv",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar("ST", dimTemperature/dimTime, 0)
    );

    volScalarField DH 
    (
        IOobject
        (
            "DH",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar("DH", dimLength*dimLength/(dimTime*dimTime), 0)
    );
    DH.oldTime();

    volVectorField SU 
    (
        IOobject
        (
            "SU",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedVector("SU", dimLength/(dimTime*dimTime), vector(0, 0, 0))
    );

