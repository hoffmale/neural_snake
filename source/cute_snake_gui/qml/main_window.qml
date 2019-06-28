import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
	id: root

	property int cellSize: 20
	property int cellSpacing: 2

	visible: true
	width: 800
	height: 480
	title: "Snake"
	color: "#ffffff"

	Item {
		focus: true

		Keys.enabled: true
		Keys.onPressed: {
			switch(event.key) {
				case Qt.Key_W:
					gameController.up();
					break;
				case Qt.Key_A:
					gameController.left();
					break;
				case Qt.Key_S:
					gameController.down();
					break;
				case Qt.Key_D:
					gameController.right();
					break;
			}
		}
	}

	Pane {
		anchors.centerIn: parent

		background: Rectangle {
			color: "#999999"
			border.width: 1
			border.color: "#000000"
		}
		
		Grid {
			id: snakeView

			anchors.margins: 10
			columns: gameState.width
			spacing: root.cellSpacing

			Repeater {
				id: snakeViewRepeater

				model: gameState

				delegate: Rectangle {
					id: snakeViewSquare

					property var colors: ["#ff0000", "#555555", "#aaaaaa", "#ffffff", "#ffffff"]

					width: root.cellSize
					height: root.cellSize

					color: colors[tile]
				}

				Component.onCompleted: {
					console.log(gameState.rowCount);
				}
			}
		}
	}
}