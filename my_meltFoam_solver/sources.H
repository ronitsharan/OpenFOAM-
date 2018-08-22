//Cellwise update of alpha for each time step


/*
forAll(mesh.cells(), celli)                      //mesh.cells()
  {
    if (T[celli] < Ts.value())
    {
      alphaTemp[celli] = 0;
    }
    else if (T[celli] > Tl.value())
    {
      alphaTemp[celli] = 1;
    }
    else
    {
      alphaTemp[celli] = (T[celli]-Ts.value())/(Tl.value()-Ts.value());
    }
  };
*/

alphaTemp = 0.5*Foam::erf(4.0*(T-Tmelt)/(Tl-Ts))+scalar(0.5);

alpha = alphaTemp;

//Info << "currentTime = " << alphaTemp.oldTime() << endl;
//Info << "oldTime = "     << alphaTemp           << endl;

ST = (- hs*fvc::ddt(alphaTemp)
     - hs*fvc::div(phi,alphaTemp));

//alpha = 0.5*Foam::erf(4.0*(T-Tmelt)/(Tl-Ts))+scalar(0.5);

//Info << "alpha = \n" << alpha << endl;

    

      
