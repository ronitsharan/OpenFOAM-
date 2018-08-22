// Solving the energy equation

{

    
   
    fvScalarMatrix TEqn
    (
        fvm::ddt(cp, T)
      + fvm::div(phi*fvc::interpolate(cp), T)
      //+ hs*4.0*exp(-pow(4.0*(T-Tmelt)/(Tl-Ts),2))/Foam::sqrt(pi)/(Tl-Ts)*fvm::ddt(T)
      //+ hs*4.0*exp(-pow(4.0*(T-Tmelt)/(Tl-Ts),2))/Foam::sqrt(pi)/(Tl-Ts)*(U & fvc::grad(T)) 
      //+ hs*fvc::ddt(alpha)
      //+ hs*fvc::div(phi,alpha)                                             //my
      - fvm::laplacian(lambda/rho, T)
      -
        ST
    );


    TEqn.relax();
    TEqn.solve();

//    TEqn().relax();
//    TEqn().solve();

    
    //alpha = 0.5*Foam::erf(4.0*(T-Tmelt)/(Tl-Ts))+scalar(0.5);                //thinner interface compared to mine, makes sense.
    //alpha = alphaLocal;

// my alpha update starts
/* 
  forAll(T, celli)
  {
    if (T[celli] < Ts.value())
    {
      alpha[celli] = 0;
    }
    else if (T[celli] > Tl.value())
    {
      alpha[celli] = 1;
    }
    else
    {
      alpha[celli] = (T[celli]-Ts.value())/(Tl.value()-Ts.value());
    }
  }
*/
// my alpha update ends

    cp = alpha*cpL+(1.0-alpha)*cpS;
    lambda = alpha*lambdaL+(1.0-alpha)*lambdaS;
    nu = alpha*nuL+(1.0-alpha)*nuS;
    rhok = 1.0 - Foam::max(beta*(T - Tl),0.0);
    DC = DCl*Foam::pow(1.0-alpha,2)/(Foam::pow(alpha,3)+DCs);

}
