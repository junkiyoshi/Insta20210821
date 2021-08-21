#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	int span = 30;
	float threshold = 0.5;
	float frame_param = ofGetFrameNum() * 0.003;
	float coordinate_param = 0.0065;

	for (int z = -300; z <= 300; z += span) {

		for (int x = -300; x <= 300; x += span) {

			for (int y = -300; y <= 300; y += span) {

				auto noise_value = ofNoise(x * coordinate_param, y * coordinate_param, z * coordinate_param, frame_param);
				if (noise_value < threshold) { continue; }

				auto noise_1 = ofNoise((x - span) * coordinate_param, y * coordinate_param, z * coordinate_param, frame_param);
				auto noise_2 = ofNoise(x * coordinate_param, (y + span) * coordinate_param, z * coordinate_param, frame_param);
				auto noise_3 = ofNoise((x + span) * coordinate_param, y * coordinate_param, z * coordinate_param, frame_param);
				auto noise_4 = ofNoise(x * coordinate_param, (y - span) * coordinate_param, z * coordinate_param, frame_param);

				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(x - span * 0.5, y - span * 0.5, z));
				vertices.push_back(glm::vec3(x + span * 0.5, y - span * 0.5, z));
				vertices.push_back(glm::vec3(x + span * 0.5, y + span * 0.5, z));
				vertices.push_back(glm::vec3(x - span * 0.5, y + span * 0.5, z));

				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
				this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

				if (noise_1 < threshold || x == -300) {

					this->frame.addVertex(vertices[0]);
					this->frame.addVertex(vertices[3]);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);
				}

				if (noise_2 < threshold || y == 300) {

					this->frame.addVertex(vertices[2]);
					this->frame.addVertex(vertices[3]);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);
				}

				if (noise_3 < threshold || x == 300) {

					this->frame.addVertex(vertices[1]);
					this->frame.addVertex(vertices[2]);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);
				}

				if (noise_4 < threshold || y == -300) {

					this->frame.addVertex(vertices[0]);
					this->frame.addVertex(vertices[1]);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);

				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());
	ofRotateX(ofGetFrameNum() * 1.5);

	ofSetColor(255);
	this->frame.draw();

	ofSetColor(0);
	this->face.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}