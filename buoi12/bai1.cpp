#include <iostream>
#include <cmath>
#include <vector>
#include <concepts>
#include <format>
#include <ranges>
#include <memory>

// Concept for numeric types we can use
template<typename T>
concept Numeric = std::floating_point<T> || std::integral<T>;

// Mathematical Vector concept
template<typename T>
concept Vector2D = requires(T a, T b) {
    { a.x } -> std::convertible_to<double>;
    { a.y } -> std::convertible_to<double>;
};

// Point structure with operator overloading
template<Numeric T>
struct Point {
    T x{}, y{};
    
    constexpr Point(T x = 0, T y = 0) noexcept : x(x), y(y) {}
    
    auto operator<=>(const Point&) const = default;
    
    Point& operator+=(const Point& p) noexcept {
        x += p.x; y += p.y;
        return *this;
    }
    
    Point operator+(const Point& p) const noexcept {
        return Point(*this) += p;
    }
    
    // Scalar multiplication
    Point operator*(T scalar) const noexcept {
        return {x * scalar, y * scalar};
    }
};

// Function traits for mathematical functions
template<Numeric T>
class Function2D {
public:
    virtual ~Function2D() = default;
    virtual T evaluate(const Point<T>& p) const = 0;
    virtual Point<T> gradient(const Point<T>& p) const = 0;
    virtual T hessianDet(const Point<T>& p) const = 0;
};

// Specific implementation for f(x,y) = x³ - 3xy²
template<Numeric T>
class CubicFunction final : public Function2D<T> {
    static constexpr T EPSILON = 1e-10;

public:
    T evaluate(const Point<T>& p) const override {
        return std::pow(p.x, 3) - 3 * p.x * std::pow(p.y, 2);
    }
    
    Point<T> gradient(const Point<T>& p) const override {
        return {
            3 * std::pow(p.x, 2) - 3 * std::pow(p.y, 2),  // ∂f/∂x
            -6 * p.x * p.y                                 // ∂f/∂y
        };
    }
    
    T hessianDet(const Point<T>& p) const override {
        T d2f_dx2 = 6 * p.x;
        T d2f_dy2 = -6 * p.x;
        T d2f_dxdy = -6 * p.y;
        return d2f_dx2 * d2f_dy2 - d2f_dxdy * d2f_dxdy;
    }

    bool isSaddlePoint(const Point<T>& p) const {
        auto grad = gradient(p);
        
        // Check if critical point
        if (std::abs(grad.x) < EPSILON && std::abs(grad.y) < EPSILON) {
            // Special case for origin
            if (std::abs(p.x) < EPSILON && std::abs(p.y) < EPSILON) {
                return true;
            }
            return hessianDet(p) < 0;
        }
        return false;
    }
};

// Analysis result structure
template<Numeric T>
struct AnalysisResult {
    Point<T> point;
    T functionValue;
    bool isSaddle;
    
    void print() const {
        std::cout << std::fixed << std::setprecision(6)
                  << "Point (" << point.x << ", " << point.y << ")\n"
                  << "Function value: " << functionValue << "\n"
                  << "Status: " << (isSaddle ? "SADDLE POINT" : "NOT A SADDLE POINT")
                  << "\n-------------------\n";
    }
};

// Main analyzer class
template<Numeric T>
class SaddleAnalyzer {
    std::unique_ptr<CubicFunction<T>> function;
    std::vector<Point<T>> points;

public:
    SaddleAnalyzer() : function(std::make_unique<CubicFunction<T>>()) {}
    
    void addPoint(const Point<T>& p) {
        points.push_back(p);
    }
    
    std::vector<AnalysisResult<T>> analyze() const {
        std::vector<AnalysisResult<T>> results;
        results.reserve(points.size());
        
        for (const auto& p : points) {
            results.push_back({
                p,
                function->evaluate(p),
                function->isSaddlePoint(p)
            });
        }
        return results;
    }
};

// Input handling
template<Numeric T>
class InputHandler {
public:
    static Point<T> getPoint(int num) {
        T x, y;
        std::cout << "Enter point " << num << " (x y): ";
        std::cin >> x >> y;
        return {x, y};
    }
    
    static int getPointCount() {
        int count;
        do {
            std::cout << "Number of points to analyze: ";
            std::cin >> count;
        } while (count < 1);
        return count;
    }
};

int main() {
    std::cout << "Saddle Point Analyzer for f(x,y) = x³ - 3xy²\n"
              << "==========================================\n";
    
    SaddleAnalyzer<double> analyzer;
    auto pointCount = InputHandler<double>::getPointCount();
    
    // Input points
    for (int i = 0; i < pointCount; ++i) {
        analyzer.addPoint(InputHandler<double>::getPoint(i + 1));
    }
    
    // Analyze and display results
    std::cout << "\nAnalysis Results:\n";
    for (const auto& result : analyzer.analyze()) {
        result.print();
    }
    
    return 0;
}
