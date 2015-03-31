program lesson2_Program3;

var PD, Dname, Cmodel : text;
    TotalKM, CostPD, TCostPD, Distance : real; 
     {real is a decimal (described later)} 
                   

begin
 
 TCostPD := 0; 
 
 {note that this is called an 'initialisation'. 
  It is important to initialise variables to 0 
  so that it is 'refreshed' from the previous 
  'rubbish' value in the memory.}

 writeln('This program prompts you to input the cost per litre of');
 writeln('the petrol/diesel you spend in and the average distance you travel');
 writeln('with your car every week. Then the computer calculates the total cost');
 writeln('you spend in fuel every week.');
 readln;
 
 write('Diesel or Petrol?: ');
 readln(PD);
 write('Name Of Driver: ');
 readln(Dname);
 write('Car Model: ');
 readln(Cmodel);
 write('Cost of Diesel/Petrol: (£) ');
 readln(CostPD);
 writeln('Average distance you travel with your car every week: (kilometres) ');
 readln(Distance);
 writeln;
 writeln;
 writeln('Name of Driver:');
 writeln('Car Model:');
 writeln('Diesel/Petrol:PD');
 writeln('Average distance covered every week: ,Distance:1:2,Km');
 writeln('Cost of PD per liter: £CostPD:1:2/litre');
 writeln;
 writeln;

 TCostPD := Distance * CostPD;
 
 writeln('Total cost of PD per week: £ ,TCostPD:1:2'); {note this,}

 TCostPD := 0;
 
 writeln('Total cost of PD per week:£,(Distance * CostPD):1:2'); {this}
 writeln('Total cost of PD per week:£,Distance * CostPD'); {and this - without ':1:2'}
 readln;
end.