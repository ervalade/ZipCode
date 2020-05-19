class BarCodeViewClass {
	#height;
	#width;
	#border;
	#html = '<canvas id="barCode" height="%h" width="%w" style="border:%bpx solid black;">Your browser does not support the HTML5 canvas tag.</canvas>';
	#parent;
	constructor(height, width, border, parent) {
		this.#height = height;
		this.#width = width;
		this.#border = border;
		this.#html = this.#html.replace("%h", this.#height);
		this.#html = this.#html.replace("%w", this.#width);
		this.#html = this.#html.replace("%b", this.#border);
		parent.insertAdjacentHTML('beforeend', this.#html);
	}
	get height() { return this.#height; }
	get width() { return this.#width; }
	get html() { return this.#html; }

	update(barCode) {
		const SPACE = 5;
		var startAt = 10;
		const HORIZONTAL_OFFSET_FOR_0 = 10;
		var barCodeView = document.getElementById("barCode");
		var ctx = barCodeView.getContext("2d");
		ctx.clearRect(0, 0, this.#width, this.#height);
		ctx.lineWidth = 1;
		var startAt = 10;

		for (let char of barCode) {
			switch (char) {
				case '1':
					ctx.moveTo(startAt, 0);
					ctx.lineTo(startAt, this.#height);
					break;
				case '0':
					ctx.moveTo(startAt, HORIZONTAL_OFFSET_FOR_0);
					ctx.lineTo(startAt, (this.#height - HORIZONTAL_OFFSET_FOR_0));
					break;
				case ' ':
					startAt += SPACE;
					break;
				default:
					break;
			}
			ctx.closePath();// if not bars are gray !
			//ctx.translate(SPACE,0);//pb with clearRect
			startAt += SPACE;
		}
		ctx.stroke();
	}
}