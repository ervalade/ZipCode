function toBarCode() {
	const ZIP_CODE=document.getElementById("zipCode").value;
	var style = window.getComputedStyle(document.getElementById("barCode"));
	const HEIGHT_PX=style.getPropertyValue("height");
	// remove px for computation and convert to int base 10
	const  HEIGHT = parseInt(HEIGHT_PX.replace('px', ''),10);
	const  SPACE = 5;
	var ctx = document.getElementById("barCode").getContext("2d");
	ctx.lineWidth = 1;
	const START_AT=10;
	const HORIZONTAL_OFFSET_FOR_0=10;
	for (let char of ZIP_CODE){
		if (char === '1') {
			ctx.moveTo(START_AT, 0);
			ctx.lineTo(START_AT, HEIGHT);
		} else {
			ctx.moveTo(START_AT, HORIZONTAL_OFFSET_FOR_0);
			ctx.lineTo(START_AT, (HEIGHT- HORIZONTAL_OFFSET_FOR_0));
		}
		ctx.stroke();
		// start=start+space;
		ctx.translate(SPACE,0);
	}
}
