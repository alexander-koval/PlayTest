#ifdef __OBJC__

#import <UIKit/UIKit.h>

@class EAGLView;
@class MainViewController;

@interface AppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    EAGLView *glView;
    MainViewController *viewController;
    UIImageView *_background;
}

+ (AppDelegate*) GetInstance;
+ (UIViewController*) GetRootViewController;
+ (UIView*) GetRootView;
- (void) initPushNotificationsWithSound: (BOOL)withSound;
- (UIImage*) GetLaunchImage;

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet EAGLView *glView;
@property (nonatomic, retain) IBOutlet MainViewController *viewController;

@end

#endif

#ifdef __cplusplus

namespace GUI
{
class Widget;
}

// Ввод текста
void ShowKeyboard();
void ShowNumericKeyboard();
void HideKeyboard();
bool IsKeyboardActive();
bool IsKeyboardVisible();
std::string GetInputText(); // Возвращает текст в textField
void SetInputText(const std::string &text); // Устанавливает текст в textField
void SetInputWidget(GUI::Widget *w);
GUI::Widget* GetInputWidget();
void SetInputCallback(std::function<int(int loc, int len, const std::string & data)> fun);

void ResetAnimationFrameInterval();

#endif
