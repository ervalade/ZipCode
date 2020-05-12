function update(barCode) {
	const SPACE = 5;
	var startAt=10;
	const HORIZONTAL_OFFSET_FOR_0=10;
	
	var barCodeView= document.getElementById("barCode");
	var ctx = barCodeView.getContext("2d");
	ctx.clearRect(0, 0, barCodeView.width, barCodeView.height);
	ctx.lineWidth = 1;
	var startAt=10;

	for (let char of barCode){
		switch (char) {
		case '1':
			ctx.moveTo(startAt, 0);
			ctx.lineTo(startAt, barCodeView.height);
			break;
		case '0':
			ctx.moveTo(startAt,HORIZONTAL_OFFSET_FOR_0);
			ctx.lineTo(startAt, (barCodeView.height - HORIZONTAL_OFFSET_FOR_0));
			break;
		case ' ':
			startAt+=SPACE;
			break;
		default:
			break;
		}
		ctx.closePath();// if not bars are gray !
		//ctx.translate(SPACE,0);//pb with clearRect
		startAt+=SPACE;
	}
		ctx.stroke();
}