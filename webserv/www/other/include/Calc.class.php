<?php

class Calc{
	public $operator;
	public $num1;
	public $num2;

	public function __construct(string $oper, int $num1, int $num2){
		$this->operator = $oper;
		$this->num1 = $num1;
		$this->num2 = $num2;
	}

	public function calculator (){
		switch($this->operator){
			case 'div' :
				$result = $this->num1 / $this->num2;
				return $result;
				break ;
			case 'mul' :
				$result = $this->num1 * $this->num2;
				return $result;
				break ;
			case 'add' :
				$result = $this->num1 + $this->num2;
				return $result;
				break ;
			case 'sub' :
				$result = $this->num1 - $this->num2;
				return $result;
				break ;
			default :
			echo "Error!:";
			return ;
		}
	}
}
