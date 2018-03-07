import sys
import os
    
class Drug():
    ID = 0;
    def __init__(self, name, dose = []):
        self.drug_dose = [];
        self.drug_dose.append(dose);
        self.drug_name = name;
        Drug.ID += 1;
        self.ID = Drug.ID;
    def __str__(self):
        return "{}({},{})".format(self.__class__.__name__, self.drug_name, self.drug_dose, self.ID);


drug_list = [ Drug("Ritalin", [5, 10, 15, 20])
            , Drug("Concerta", [36, 72])
            , Drug("Effexor", [225])
            , Drug("Xanax", [0.125, 0.25, 0.5, 1, 2])
            , Drug("Akton", [1, 2, 3, 4])
            , Drug("Stilnoct", [5, 10])
            ]

max_selection = 0;
for d in drug_list:
    print("[%d] %s" %(d.ID, d.drug_name));
    max_selection += 1;
    
print();
user_selection = 999;
while (user_selection > max_selection or len(user_selection) > 1):
    user_selection = sys.stdin.readline();


print(user_selection)