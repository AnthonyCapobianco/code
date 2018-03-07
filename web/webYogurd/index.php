<?php
        
class Drug
{
        
        private $name = "";
        private $doses = [];
        
        public
        function __construct($drugName, $drugDoses) 
        {
                $this->name = $drugName;
                
                foreach ($drugDoses as $d => $dose) $this->doses[$d] = $dose;
        }
        
        public
        function printName() 
        {
                echo $this->name;
        }
        
        public 
        function printDoses() 
        {
                foreach ($this->doses as $d => $dose) printf("\n%d", $dose);
        }
}
        
$ritalin = new Drug("ritalin", [5, 10, 15, 20]);

$ritalin->printName();
$ritalin->printDoses();

        
?>