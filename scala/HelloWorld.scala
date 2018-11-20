object HelloWorld {
	def main(args: Array[String]) {

		val name = "Anthony";

		var i = 0;

		for (len <- name) {
			i += 1;
		}

		println(i);
		
	}
}