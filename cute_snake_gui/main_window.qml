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

	Pane {
		anchors.centerIn: parent

		background: Rectangle {
			color: "#999999"
			border.width: 1
			border.color: "#000000"
		}
		
		Grid {
			id: snakeView

			property alias snakeBoard: snakeViewRepeater.model

			anchors.margins: 10
			columns: 30
			spacing: root.cellSpacing

			Repeater {
				id: snakeViewRepeater

				model: 15*30

				delegate: Rectangle {
					id: snakeViewSquare

					width: root.cellSize
					height: root.cellSize

					color: "#555555"
				}
			}
		}
	}
}