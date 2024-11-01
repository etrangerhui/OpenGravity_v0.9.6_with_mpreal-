m1=2e17;m2=2e17;m3=2e17;m=[m1,m2,m3];
r=vpa(1.e4,100);
y0=init(m,r*10,3,2);
tspan = [0 831400];
t=[];y=[];
G = 6.67430e-11; 

% y0 = [0.5, sqrt(3)/2, 0, -sqrt(3)/2, 0, 0, 1, 0, 0, 0, 0, 0];
fp=fopen('test.unv','w');kk=2;
fprintf(fp,'%d\n',length(m));rv= reshape(y0,[kk,length(m)*kk]);
for i=1:length(m)
  fprintf(fp,'%s %s %f    %f %f   %s %s %f %d %f\n',rv(1,2*i-1),rv(2,2*i-1),0,m(i),r,rv(1,2*i),rv(2,2*i),0,i,norm(rv(1:2,2*i)));
end



y1=y0;
dydt=myODE(t, y1, G, m);

  options = odeset('RelTol',1.0e-10,'AbsTol',1.0E-10);
  [t, y] = ode113(@(t,y) myODE(t, y, G,m ), tspan, y0,options);

% y1=[1.0;-1.0;0.0;0.0;1.0;3.0;0.0;0.0;-2.0;-1.0;0.0;0.0];
%  [t, y] = ode113(@(t,y) myODE(t,y , 1,[5,3,4]), [0,63],y1 ,options);
% dydt=myODE(t, y1, 1, [5,3,4]);
% dydt1=funkshun(t,y1,1,[5,3,4]);
 figure(6);plot(y(:,1), y(:,2),'b', y(:,5), y(:,6), 'r', y(:,9), y(:,10), 'g');axis equal

for j=1:length(t)
   rv= reshape(y(j,:),[kk,length(m)*kk]);
   for i=1:length(m)
      fprintf(fp,'%g %g %g    %g %g   %g %g %g %d %g %d\n',rv(1,2*i-1),rv(2,2*i-1),0,m(i),r,rv(1,2*i),rv(2,2*i),0,i,norm(rv(1:2,2*i)),t(j));
   end
end
y1=y0';
y2=zeros(fix(max(tspan)/100),length(m)*kk*2);
for j=1:fix(max(tspan)/100)
   y2(j,:)=y1;
   for k=1:100
     dydt=myODE(t, y1, G,-m);  
     y1=y1+dydt;
   end
   rv= reshape(y1,[kk,length(m)*kk]);
   for i=1:3
      fprintf(fp,'%g %g %g    %g %g   %g %g %g %d %g %d\n',rv(1,2*i-1),rv(2,2*i-1),0,m(i),r,rv(1,2*i),rv(2,2*i),0,i,norm(rv(:,2*i)),j*100);
   end
end
fclose(fp);

figure(7);plot(y2(:,1), y2(:,2),'b', y2(:,5), y2(:,6), 'r', y2(:,9), y2(:,10), 'g');axis equal
function dydt = myODE(t, y, G, m)
    k=2;
    n=length(m);
    rv= reshape(y,[k,n*2]);
    dydt=rv;
    for i=1:n
        dydt(:,2*i-1)=rv(:,2*i);
        dydt(:,2*i)=dydt(:,2*i)*0;
        for j=1:n
           dr=rv(:,2*j-1)-rv(:,2*i-1);
           nr=norm(dr);
           if nr>0
             dydt(:,2*i)=dydt(:,2*i)+ G*dr/nr^3*abs(m(j));
           end
        end
        if any(m<0),dydt(:,2*i-1)=dydt(:,2*i-1)+dydt(:,2*i);end
    end
    
    dydt=dydt(:);
end

function yd=funkshun (t,y,G,m) % funkshun solves the RHS of the three-body ODE system.

%  Parameters:

%    Input: T--> value of the time parameter.
%           Y(12)-->the solution for a given T value.

%    Output, real YDOT(12), the derivatives of the current solution.

  m0=m(1);
  m1=m(2);
  m2=m(3);
  y=y(:);
  x0=y(1:2);
  x1=y(5:6);
  x2=y(9:10);

%These ds (vectors represent the reciprocal of square the distance
%(in direction of the displacement between the two bodies)and here
%we compute them to fit in Newton's law:

  d0=(x2-x1)/norm(x2-x1)^3;
  d1=(x0-x2)/norm(x0-x2)^3;
  d2=(x1-x0)/norm(x1-x0)^3;

%For the three bodies, we compute the 12 elements of yd to be as follows:

  yd(1:2)=y(3:4);
  yd(3:4)=m1*d2-m2*d1;
  yd(5:6)=y(7:8);
  yd(7:8)=m2*d0-m0*d2;
  yd(9:10)=y(11:12);
  yd(11:12)=m0*d1-m1* d0;

  yd=yd(:);
  
  return
end
function y0=init(m,rr,v0,w0)
  n=length(m);
   ang=2*pi/n;
   rc=[0,0];
   for i=1:n
       a=(i-1)*ang+pi/2;
       r(i,:)=rr*[cos(a),sin(a)];
       rc=rc+r(i,:)*m(i);
   end
   rc=rc/sum(m);L=0;
   for i=1:n
       dr(i,:)=r(i,:)-rc;
       L=L+norm(dr(i,:));
   end
   L=L/n;
G = 6.67430e-11; 
   v1=100;
   vc=[0,0];w=1;
while abs(v1-w)>1.e-8
   w=v1;
   for i=1:n
       v(i,:)=vc+dr(i,:)/L*v0+[-dr(i,2),dr(i,1)]/norm(dr(i,:))*(w+w0);
   end
   y0=[];
   for i=1:n
       y0=[y0,r(i,:),v(i,:)];
   end
   dydt=myODE([], y0, G, m);
    k=2;
    rv= reshape(dydt,[k,n*2]);
    v1=0;
    for i=1:n
        v1=v1+sqrt(norm(rv(:,2*i))*norm(dr(i,:)));
    end
    v1=v1/n;
end
end
