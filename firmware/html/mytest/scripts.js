function openNav() {
  menuopen = true;//window.innerWidth<window.innerHeight;
  document.getElementById("menubtn").style.visibility = "hidden";
  document.getElementById("mySidebar").style.width = "250px";
  if(!menuover) {
    document.getElementById("main").style.marginLeft = "250px";
  } else {
    document.getElementById("main").style.marginLeft = "0";
  }
}

function closeNav() {
  menuopen = false;
  document.getElementById("mySidebar").style.width = "0";
  document.getElementById("main").style.marginLeft= "0";
  document.getElementById("menubtn").style.visibility = "visible";
}

var menuopen = window.innerWidth>window.innerHeight;
var menuover = false;
function onResize() {
	//if(screen.width<screen.hight) {
	if(window.innerWidth<window.innerHeight) {
		menuover = true;
		//closeNav();
	} else {
		menuover = false;
		//openNav();
	}
	if(menuopen) {
	  openNav();
	} else {
	  closeNav();
	}
}


function updVal(id, val) {
  document.getElementById(id).value = val;
}
