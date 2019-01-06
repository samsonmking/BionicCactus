#include <web/Header.hpp>

int Header::getHeader(char *out, size_t len) {
    const char *header = R"(<html>
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>BionicCactus</title>
		<style>
		body {
  			font-family: Sans-Serif;
		}
		ul {
			list-style-type: none;
			margin: 0;
    		padding: 0;
		}
		a {
			text-decoration: none;
		}
		.progressLabel {
			font-weight: bold;
			margin-bottom: 10px;
		}
		.progressOuter {
			width: 200px;
			background-color: lightgray;
		}
		.progressInner {
			height: 30px;
			text-align: center;
			line-height: 30px;
			color: white;
		}
		</style>
    </head>
	<body>
	    <table>
			<tr>
				<td width="60">
					<svg version="1.1" id="Capa_1" x="0px" y="0px" height="48" width="48" viewBox="0 0 387.334 387.334" style="enable-background:new 0 0 387.334 387.334;">
					<path id="XMLID_136_" style="fill:#61D338;" d="M387.334,147.751v103.315c0,2.652-1.054,5.196-2.929,7.071l-126.27,126.268
						c-1.876,1.875-4.419,2.929-7.071,2.929H136.271c-2.652,0-5.195-1.054-7.071-2.929L2.929,258.137C1.054,256.262,0,253.718,0,251.066
						V147.751c0-5.523,4.478-10,10-10h22.961c2.652,0,5.195,1.054,7.071,2.929L167.97,268.619l71.914-143.826l-46.216-92.432
						l-46.218,92.432l34.287,68.57c2.47,4.939,0.468,10.946-4.472,13.417c-4.943,2.469-10.947,0.468-13.417-4.472l-36.523-73.042
						c-1.407-2.815-1.407-6.129,0-8.944L184.724,5.528C186.418,2.141,189.881,0,193.668,0c3.788,0,7.25,2.14,8.944,5.528l57.396,114.792
						c1.407,2.815,1.407,6.129,0,8.944L179.771,289.74c-0.313,0.671-2.309,3.188-2.971,3.695c-1.599,1.23-3.494,1.817-5.402,2.043
						c-4.397,0.522-7.588-2.723-7.891-3.038L28.818,157.751H20v89.173l120.412,120.41h106.51l120.412-120.41v-89.173h-8.818
						L223.698,292.572c-3.906,3.905-10.236,3.906-14.143,0c-3.905-3.905-3.905-10.237,0-14.142l137.746-137.75
						c1.875-1.875,4.419-2.929,7.071-2.929h22.961C382.856,137.751,387.334,142.228,387.334,147.751z"/>
					</svg>
				</td>
				<td style="vertical-align: center; font-size: xx-large; font-weight: bold;">
					<a href="/">BionicCactus</a>
				</td>
			</tr>
		</table>)";
    return snprintf(out, len, header);
}