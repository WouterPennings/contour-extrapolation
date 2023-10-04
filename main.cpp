#include <opencv2/opencv.hpp>

int main() {
    // Open the input video file
    cv::VideoCapture inputVideo("spiderman.mp4");

    // Check if the video file opened successfully
    if (!inputVideo.isOpened()) {
        std::cerr << "Error: Could not open the input video file." << std::endl;
        return 1;
    }

    // Get video properties
    int frameWidth = static_cast<int>(inputVideo.get(cv::CAP_PROP_FRAME_WIDTH));
    int frameHeight = static_cast<int>(inputVideo.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = inputVideo.get(cv::CAP_PROP_FPS);

    // Define the codec and create a VideoWriter object for the output video
    cv::VideoWriter outputVideo("grey_spiderman_cpp.mp4", cv::VideoWriter::fourcc('X', '2', '6', '4'), fps, cv::Size(frameWidth, frameHeight), false);

    // Check if the VideoWriter opened successfully
    if (!outputVideo.isOpened()) {
        std::cerr << "Error: Could not create the output video file." << std::endl;
        return 1;
    }

    // Process each frame of the input video
    cv::Mat frame;
    while (inputVideo.read(frame)) {
        // Convert the frame to grayscale
        cv::Mat grayscaleFrame;
        cv::cvtColor(frame, grayscaleFrame, cv::COLOR_BGR2GRAY);

        // Write the grayscale frame to the output video
        outputVideo.write(grayscaleFrame);
    }

    // Release the video capture and writer objects
    inputVideo.release();
    outputVideo.release();

    std::cout << "Grayscale video saved as 'grey_spiderman.mp4'." << std::endl;
    std::cout << "FPS of video"<< fps << std::endl;

    return 0;
}
