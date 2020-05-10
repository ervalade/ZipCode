class BarCodeView {
	#height;
	#width;
	#border;
	#html='<canvas id="barCode" style="height:%hpx;width:%wpx;border:%bpx solid black;">Your browser does not support the HTML5 canvas tag.</canvas>';
	#parent;
	constructor(height,width,border,parent)
	{
		this.#height=height;
		this.#width=width;
		this.#border=border;
		this.#html=this.#html.replace("%h",this.#height);
		this.#html=this.#html.replace("%w",this.#width);
		this.#html=this.#html.replace("%b",this.#border);
		parent.insertAdjacentHTML('beforeend',this.html);
	}
	get height(){return this.#height;}
	get width(){return this.#width;}
	get html(){return this.#html;}

	update(value) {
		// remove px for computation and convert to int base 10
		const  SPACE = 5;
		var ctx = document.getElementById("barCode").getContext("2d");
		ctx.lineWidth = 1;
		const START_AT=10;
		const HORIZONTAL_OFFSET_FOR_0=10;
		for (let char of value){
			if (char === '1') {
				ctx.moveTo(START_AT, 0);
				ctx.lineTo(START_AT, this.#height);
			} else {
				ctx.moveTo(START_AT, HORIZONTAL_OFFSET_FOR_0);
				ctx.lineTo(START_AT, this.#height- HORIZONTAL_OFFSET_FOR_0);
			}

			ctx.stroke();
			// start=start+space;
			ctx.translate(SPACE,0);
		}
	}
};

//barCodeView=new BarCodeView(100,500,1,'document.body');
//console.log(barCodeView.html);